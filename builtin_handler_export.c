/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_export(t_minishell *shell, t_builtin_param param)
{
	size_t	index;

	if (param.argc == 1)
		builtin_handler_env(shell, param);
	else
	{
		index = 1;
		while (index < param.argc)
		{
			env_set_from_line(param.argv[index]);
			index++;
		}
	}
}