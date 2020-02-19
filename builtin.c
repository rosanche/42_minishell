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
		.name = BIN_ECHO
	},
	{
		.handler = builtin_handler_cd,
		.name = BIN_CD
	},
	{
		.handler = &builtin_handler_pwd,
		.name = BIN_PWD
	},
	{
		.handler = &builtin_handler_export,
		.name = BIN_EXPORT
	},
	{
		.handler = NULL,
		.name = BIN_UNSET
	},
	{
		.handler = &builtin_handler_env,
		.name = BIN_ENV
	},
	{
		.handler = &builtin_handler_exit,
		.name = BIN_EXIT
	},
};
