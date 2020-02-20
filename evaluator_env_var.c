/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:42:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 18:42:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	evaluate_env_var(char *line, size_t *consumed, t_arrlst *chrlst)
{
	if (*line != '$')
		return (0);
	line++;
	*consumed += 1;

	return (0);
}
