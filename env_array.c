/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 10:53:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 10:53:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env_array = NULL;
int		g_env_array_valid = 0;

char
	**env_array_get(t_minishell *shell)
{
	if (!g_env_array_valid)
		env_array_build(shell);
	return (g_env_array);
}

void
	env_array_invalidate(void)
{
	ft_free_and_release((void **)(&g_env_array));
	g_env_array_valid = 0;
}

void
	env_array_build(t_minishell *shell)
{
	size_t		index;
	t_env_var	*var;

	ft_printf("env array building...\n");
	env_array_invalidate();
	if (!(g_env_array = malloc((g_env_variables.size + 1) * sizeof(void *))))
		return ;
	index = 0;
	while (index < g_env_variables.size)
	{
		var = (t_env_var *)(g_env_variables.items[index]);
		g_env_array[index] = ft_strjoin3(var->name, "=", var->value);
		index++;
	}
	g_env_array[index] = NULL;
	g_env_array_valid = 1;
	ft_printf("env array building done\n");
}
