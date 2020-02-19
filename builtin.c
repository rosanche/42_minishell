/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:18:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:18:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	g_builtin[] = {
	{
		.handler = &builtin_handler_echo,
		.name = "echo"
	},
	{
		.handler = builtin_handler_cd,
		.name = "cd"
	},
	{
		.handler = &builtin_handler_pwd,
		.name = "pwd"
	},
	{
		.handler = NULL,
		.name = "export"
	},
	{
		.handler = NULL,
		.name = "unset"
	},
	{
		.handler = NULL,
		.name = "env"
	},
	{
		.handler = &builtin_handler_exit,
		.name = "exit"
	},
};
