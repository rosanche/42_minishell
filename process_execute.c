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
	if (WIFEXITED(status))
		g_shell->last_code = WEXITSTATUS(status);
	close(p[1]);
	*fd_in = p[0];
}

static void
	execute(t_process *process)
{
	char **argv;

	arraylist_add_int(g_shell->pidlst, process->pid);
	argv = (char **)process->arglst->items;
	if (execve(process->filepath, argv, env_array_get()) == -1)
	{
		minishell_error(g_shell, process->name, strerror(errno));
		arraylist_remove(g_shell->pidlst, process->pid, NULL);
		exit(EXIT_FAILURE);
	}
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
		process = (t_process*)processlst->items[index];
		index++;
		if (process->b_err == 0)
		{
			pipe(p);
			if ((process->pid = fork()))
				wait_pid(p, &fd_in);
			else
			{
				dup2(fd_in, IN);
				if (index < processlst->size)
					dup2(p[1], OUT);
				close(p[0]);
				if (minishell_evaluate_builtin(g_shell, process))
					exit(EXIT_SUCCESS);
				else if (process_find_path(process))
					execute(process);
				else
					minishell_error(g_shell, process->name, ERR_CMD_NOT_FOUND);
				exit(EXIT_FAILURE);
			}
		}
	}
}
