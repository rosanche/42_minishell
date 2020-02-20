/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_quit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:01:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 15:01:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_quit = 0;

void
	signal_handler_quit(int sig)
{
	ft_printf("Handled: %s (%d)\n", "QUIT", sig);
}

int
	signal_has_quit(int and_reset)
{
	int	value;

	value = g_signal_quit;
	if (and_reset)
		g_signal_quit = 0;
	return (value);
}
