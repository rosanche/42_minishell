/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_matcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:45:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:45:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin
	*builtin_match(char *name)
{
	size_t	index;

	index = 0;
	while (index < BUILTIN_COUNT)
	{
		if (ft_strcmp(g_builtin[index].name, name) == 0)
			return (g_builtin + index);
		index++;
	}
	return (NULL);
}
