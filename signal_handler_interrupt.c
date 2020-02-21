/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_interrupt.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:50:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 14:50:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_interrupt = 0;

void
	signal_handler_interrupt(int sig)
{
	minishell_prompt_ask(g_shell, 1);
	g_shell->last_code = 1;
	g_signal_interrupt = 1;
	if (g_shell->pidlst->size != 0)
		minishell_process_kill(g_shell, sig);
//	if (INTERRUPT_DOES_EXIT)
//		exit(1);
}

int
	signal_has_interrupt(int and_reset)
{
	int	value;

	value = g_signal_interrupt;
	if (and_reset)
		g_signal_interrupt = 0;
	return (value);
}
