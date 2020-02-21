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

void
	process_execute(t_process *process)
{
	char	**argv;
	void	*pid_as_ptr;

	if (process->is_dir)
	{
		minishell_error_file(g_shell, process->filepath, EISDIR);
		return ;
	}
	process->pid = fork();
	if (process->pid == 0)
	{
		dup2(process->in_fd == -1 ? IN : process->in_fd, IN);
		dup2(process->out_fd == -1 ? OUT : process->out_fd, OUT);
		argv = (char **)process->arglst->items;
		execve(process->filepath, argv, env_array_get());
	}
	else
	{
		pid_as_ptr = (void *)((long)0 + process->pid);
		arraylist_add(g_shell->pidlst, pid_as_ptr);
	}
}
