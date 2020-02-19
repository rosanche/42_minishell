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
	char	*equal;

	equal = ft_strchr(line, '=');
	if (equal == NULL)
		return ;
	equal[0] = '\0';
	equal++;
	env_set(line, equal);
}

void
	env_set(char *name, char *value)
{
	t_env_var	*var;

	if (!(var = (t_env_var *)malloc(sizeof(t_env_var))))
		return ;
	var->name = ft_strdup(name);
	var->value = ft_strdup(value);
	if (var->name == NULL || var->value == NULL
			|| !arraylist_add(&g_env_variables, var))
		env_free_var(var);
}
