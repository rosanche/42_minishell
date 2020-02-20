/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_tilde.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:57:36 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 18:57:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	evaluate_tilde(char *line, size_t *consumed, t_arrlst *chrlst)
{
	char	*home;

	if (*line != '~')
		return (0);
	*consumed += 1;
	home = utility_find_home_dir();
	argument_builder_add_string(chrlst, home, 0);
	return (1);
}
