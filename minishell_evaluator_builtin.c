/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluator_builtin.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:16:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 12:16:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	minishell_evaluate_builtin(t_minishell *shell, t_arrlst *arglst)
{
	char		*name;
	t_builtin	*builtin;

	if (arglst->size == 0 || (name = arglst->items[0]) == NULL)
		return (0);
	builtin = builtin_match(name);
	if (builtin)
	{
		(*(builtin->handler))(shell, (t_builtin_param) {
			name, arglst->size - 1, (char **)(arglst->items), OUT, ERR
		});
		return (1);
	}
	return (0);
}
