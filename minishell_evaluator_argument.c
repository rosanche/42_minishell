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
	minishell_evaluate_argument(t_arrlst *arglst, char *line)
{
	int			ret;
	t_arrlst	chrlst;
	size_t		consumed;

	argument_builder_debug(1);
	while (1)
	{
		arg_builder_initialize(&chrlst);
		consumed = 0;
		ret = eval_next(line, &consumed, &chrlst);
		line += consumed;
		while (ft_iswspace(*line))
			line++;
		arraylist_add(arglst, arg_builder_build(&chrlst));
		arg_builder_finalize(&chrlst);
		argument_builder_debug_new();
		if (ret != TOKEN_KIND_STRING)
			break ;
	}
}
