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

void
	minishell_evaluate(t_minishell *shell, char *line)
{
	t_arrlst	arglst;

	arraylist_init(&arglst, NULL, 5);
	minishell_evaluate_argument(&arglst, line);
	if (!minishell_evaluate_builtin(shell, &arglst))
	{
		minishell_error(shell, (char *)(arglst.items[0]), ERR_CMD_NOT_FOUND);
	}
}
