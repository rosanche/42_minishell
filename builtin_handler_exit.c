/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_exit(t_minishell *shell, int argc, char **argv)
{
	char	code;

	if (argc == 1)
		code = 0;
	else
	{
		if (ft_str_isdigit(argv[1], 1, 1))
		{
			code = (char)ft_atoi(argv[1]);
			if (argc > 2)
				builtin_error(shell, "exit", NULL, "too many arguments");
			else
				minishell_exit(shell, code);
		}
		else
		{
			builtin_error(shell, "exit", argv[1], "numeric argument required");
			minishell_exit(shell, (char)255);
		}
	}
}
