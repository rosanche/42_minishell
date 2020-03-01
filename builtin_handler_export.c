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

static void
	builtin_handler_export_print_value(t_builtin_param param, t_env_var *var)
{
	size_t	index;
	char	current;

	index = 0;
	while ((current = var->value[index]))
	{
		if (current == Q_DOUBLE || current == '\\')
			ft_putchar_fd('\\', param.fd_out);
		ft_putchar_fd(current, param.fd_out);
		index++;
	}
}

static void
	builtin_handler_export_print(t_builtin_param param)
{
	size_t		index;
	t_env_var	*var;

	index = 0;
	while (index < g_env_variables.size)
	{
		var = (t_env_var *)g_env_variables.items[index];
		ft_dprintf(param.fd_out, "declare -x %s", var->name);
		if (var->value != NULL)
		{
			ft_putchar_fd('=', param.fd_out);
			ft_putchar_fd('"', param.fd_out);
			builtin_handler_export_print_value(param, var);
			ft_putchar_fd('"', param.fd_out);
		}
		ft_putchar_fd('\n', param.fd_out);
		index++;
	}
}

void
	builtin_handler_export(t_builtin_param param)
{
	int		index;
	char	*line;

	if (param.argc == 1)
		builtin_handler_export_print(param);
	else
	{
		index = 1;
		while (index < param.argc)
		{
			line = param.argv[index];
			if (!env_var_is_name_valid(line, 1))
				builtin_error(g_shell, param, line, ERR_NOT_VALID_ID);
			else
				env_set_from_line(line, 0);
			index++;
		}
	}
}
