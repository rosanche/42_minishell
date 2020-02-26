/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:40:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 18:40:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	wait_pid(int p[], int *fd_in)
{
	int status;

	status = 0;
	wait(&status);
	g_shell->last_pid = 0;
	if (WIFEXITED(status))
		g_shell->last_code = WEXITSTATUS(status);
	close(p[1]);
	*fd_in = p[0];
}

static void
	execute(t_process *process)
{
	char **argv;

	argv = (char **)process->arglst->items;
	if (execve(process->filepath, argv, env_array_get()) == -1)
	{
		minishell_error(g_shell, process->name, strerror(errno));
		g_shell->last_pid = 0;
		exit(EXIT_FAILURE);
	}
}

static void
	child(t_process *process, int fd_in, int has_more, int p[2])
{
	int		fd_out;

	fd_out = has_more ? p[1] : OUT;
	fd_out = process->out_fd == -1 ? fd_out : process->out_fd;
	dup2(fd_in, IN);
	dup2(fd_out, OUT);
	close(p[0]);
	if (minishell_evaluate_builtin(process, 0))
		exit(EXIT_SUCCESS);
	else if (process_find_path(process))
		execute(process);
	else
		minishell_error(g_shell, process->name, ERR_CMD_NOT_FOUND);
	exit(EXIT_FAILURE);
}

static void
	sensitive_child(t_process *process, int fd_in, int has_more, int p[2])
{
	int		fd_out;
	int		old_fd[2];

	old_fd[0] = dup(IN);
	old_fd[1] = dup(OUT);
	fd_out = has_more ? p[1] : OUT;
	fd_out = process->out_fd == -1 ? fd_out : process->out_fd;
	dup2(fd_in, IN);
	dup2(fd_out, OUT);
	close(p[0]);
	minishell_evaluate_builtin(process, 1);
	dup2(old_fd[0], IN);
	dup2(old_fd[1], OUT);
}

void
	process_execute_list(t_arrlst *processlst)
{
	t_process	*process;
	size_t		index;
	int			p[2];
	int			fd_in;

	index = 0;
	fd_in = 0;
	while (index < processlst->size)
	{
		process = (t_process *)processlst->items[index];
		fd_in = process->in_fd == -1 ? fd_in : process->in_fd;
		index++;
		if (process->b_err == 0)
		{
			pipe(p);
			if ((process->sentitive = buildin_test_sensitive(process)))
				sensitive_child(process, fd_in, index < processlst->size, p);
			if ((process->pid = fork()))
			{
				g_shell->last_pid = process->pid;
				wait_pid(p, &fd_in);
			}
			else
				child(process, fd_in, index < processlst->size, p);
		}
	}
}
