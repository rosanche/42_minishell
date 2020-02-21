/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process_kill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 19:04:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 19:04:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_process_kill(t_mshell *shell, int sig)
{
	size_t	index;
	pid_t	pid;

	index = 0;
	while (index < shell->pidlst->size)
	{
		pid = (pid_t)shell->pidlst->items[index];
		kill(pid, sig);
		index++;
	}
}
