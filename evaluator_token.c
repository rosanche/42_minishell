/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:26:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:26:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_printf("ret = %d..%d, diff = %d\n", ret, 0 + consumed, line - start);
** ft_printf("skipped space\n");
*/

int
	evaluate_token(t_arrlst *arglst, char *line, size_t *consumed)
{
	int			ret;
	size_t		sub;
	t_arrlst	chrlst;

	argument_builder_debug(1);
	while (1)
	{
		argument_builder_initialize(&chrlst);
		sub = 0;
		ret = evaluate_next(line, &sub, &chrlst);
		ft_printf("||%d||", 0 + sub);
		line += sub;
		while (ft_iswspace(*line))
		{
			line++;
			sub++;
		}
		if (ret == TOKEN_KIND_ARG_GROUP)
			arraylist_add(arglst, argument_builder_build(&chrlst));
		argument_builder_finalize(&chrlst);
		argument_builder_debug_new();
		*consumed += sub;
		if (ret != TOKEN_KIND_ARG_GROUP)
			break ;
	}
	return (arglst->size == 0 ? ret : TOKEN_KIND_ARG_GROUP);
}

void
	evaluate_tokens(t_arrlst *tokenlst, char *line, size_t *consumed)
{
	int			ret;
	size_t		sub;
	t_arrlst	*arglst;

	while (*line)
	{
		arglst = arraylist_create(10, NULL);
		sub = 0;
		ret = evaluate_token(arglst, line, &sub);
		line += sub;
		*consumed += sub;
		if (ret == TOKEN_KIND_ARG_GROUP)
			arraylist_add(tokenlst, token_create_arg_group(arglst, 1));
		else
		{
			arraylist_destroy(arglst);
			if (ret >= TOKEN_KIND_INPUT_FILE && ret <= TOKEN_KIND_APPEND_FILE)
			{
				arraylist_add(tokenlst, token_create_io_file(ret, ""));
				line += ret == TOKEN_KIND_APPEND_FILE;
			}
			else if (ret == TOKEN_KIND_PIPE)
				arraylist_add(tokenlst, token_create(TOKEN_KIND_PIPE, NULL));
			line += 1;
		}
	}
}
