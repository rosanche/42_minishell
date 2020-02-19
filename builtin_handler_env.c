/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_env(t_minishell *shell, int argc, char **argv)
{
	size_t		index;
	t_env_var	*item;

	index = 0;
	while (index < g_env_variables.size)
	{
		item = (t_env_var *)g_env_variables.items[index];
		ft_printf("%s=%s\n", item->name, item->value);
		index++;
	}
}
