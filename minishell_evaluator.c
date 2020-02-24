/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:16:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 12:16:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	minishell_evaluate_next_tokens(t_arrlst **tokenlst, size_t *sub, char *line)
{
	if (!(*tokenlst = arraylist_create(10, NULL)))
		return (0);
	return (eval_tokens(*tokenlst, line, sub));
}

static void
	wait_pids(void)
{
	pid_t	pid;

	while (g_shell->pidlst->size != 0)
	{
		pid = (pid_t)(0 + g_shell->pidlst->items[0]);
		waitpid(pid, &(g_shell->last_code), 0);
		arraylist_remove_at(g_shell->pidlst, 0, NULL);
	}
}

static int
	minishell_execute_process(t_mshell *shell, t_arrlst *processlst)
{
	t_process	*process;
	size_t		index;
	int			err;

	err = 0;
	index = 0;
	while (index != processlst->size)
	{
		process = (t_process *)processlst->items[index];
		index++;
		if (process == NULL)
			break ;
		arraylist_add(process->arglst, NULL);
		process->name = process->arglst->items[0];
		process->name = process->name == NULL ? NULL : ft_strdup(process->name);
		if (process->name == NULL)
		{
			minishell_error_simple(shell, ERR_UNEXPECTED);
			err = 1;
			break;
		}
	}

	int p[2];
	int fd_in = 0;

	index = 0;
	while (index < processlst->size)
	{
		process = (t_process*)processlst->items[index];
		index++;
		if (process->b_err == 0)
		{
			if (minishell_evaluate_builtin(shell, process))
				;
			else if (process_find_path(process))
			{
				//process_execute(process);

				pipe(p);


				if ((process->pid = fork()) == -1)
				{
					exit(EXIT_FAILURE);
				}
				else if (process->pid)
				{
					int status = 0;
					wait(&status);
					if (WIFEXITED(status))
						g_shell->last_code = WEXITSTATUS(status);
					close(p[1]);
					fd_in = p[0]; //save the input for the next command
				}
				else
				{
					dup2(fd_in, 0);
					if (index < processlst->size)
						dup2(p[1], 1);
					close(p[0]);

					char **argv = (char **)process->arglst->items;
					execve(process->filepath, argv, env_array_get());

					exit(EXIT_FAILURE);
				}

			}
			else
				minishell_error(shell, process->name, ERR_CMD_NOT_FOUND);
		}
	}


	arraylist_clear(processlst, &process_destroy);
	wait_pids();
	return (err);
}

void
	minishell_evaluate(t_mshell *shell, char *line)
{
	t_arrlst	*processlst;
	size_t		sub;
	t_arrlst	*tokenlst;
	int			ret;
	int			err;

	while (1)
	{
		sub = 0;
		ret = minishell_evaluate_next_tokens(&tokenlst, &sub, line);
		processlst = arraylist_create(5, NULL);
		executor_builder(tokenlst, processlst);
		err = minishell_execute_process(shell, processlst);
		arraylist_destroy(processlst);
		arraylist_clear(tokenlst, &token_destroy_sub);
		arraylist_destroy(tokenlst);
		line += sub;
		if (*line == '\0' || !ret || err)
			break ;
	}
}
