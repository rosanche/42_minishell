/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:04:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 19:04:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env_set_from_line(char *line)
{
	t_env_var	*var;

	var = env_var_create_from_line(line);
	if (var == NULL)
		return ;
	env_set(var);
}

void
	env_set(t_env_var *var)
{
	if (var == NULL)
		return ;
	arraylist_remove(&g_env_variables, var->name, &env_var_free);
	arraylist_add(&g_env_variables, var);
}
