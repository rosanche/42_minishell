/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:16:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 12:16:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell2.h"

void
	minishell_evaluate(t_minishell *shell, char *line)
{
	t_arrlst	arglst;
	char		*name;

	arraylist_init(&arglst, NULL, 5);
	minishell_evaluate_argument(&arglst, line);
	arraylist_add(&arglst, NULL);
	name = arglst.items[0];
	if (!minishell_evaluate_builtin(shell, &arglst))
		if (!exec(name, env_array_get(shell), (char **)arglst.items))
			minishell_error(shell, name, ERR_CMD_NOT_FOUND);
	arraylist_clear(&arglst, &free);
	arraylist_destroy_items(&arglst);
}
