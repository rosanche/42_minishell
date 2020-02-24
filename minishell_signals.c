/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:48:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 14:48:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void
	signal_handler(int sig)
{
	ft_printf("child %d\n", sig);
}

int
	minishell_signals_attach(void)
{
//	if (signal(SIGINT, &signal_handler_interrupt) == SIG_ERR)
//		return (0);
	if (signal(SIGQUIT, &signal_handler_quit) == SIG_ERR)
		return (0);
	if (signal(SIGCHLD, &signal_handler) == SIG_ERR)
		return (0);
	return (1);
}
