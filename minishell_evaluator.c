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
	char		**split;
	t_builtin	*builtin;

	split = ft_split(line, ' ');
	builtin = builtin_match(split[0]);
	if (builtin)
		(*(builtin->handler))(shell, (t_builtin_param) {
			split[0], ft_split_length(split), split, OUT, ERR
		});
	else
		minishell_error(shell, split[0], ERR_CMD_NOT_FOUND);
	ft_split_free(&split);
}
