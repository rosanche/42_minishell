/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:22:10 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 19:22:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** [a-zA-Z_]+[a-zA-Z0-9_]*
*/

int
	env_var_is_name_valid(char *name, int allow_equal)
{
	size_t	index;

	if (name == NULL)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	index = 0;
	name++;
	while (*name)
	{
		if (allow_equal && *name == '=')
			break ;
		if (!ft_isalnum(*name) && !ft_isdigit(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}
