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
** ft_printf("||%d||", 0 + sub);
** ft_printf(",%c,", *line);
** ft_printf("kind %d, sub %d, line %s\n", kind, 0 + sub, line);
*/

static int
	next_token(t_arrlst *arglst, char *line, size_t *consumed)
{
	int			ret;
	size_t		sub;
	t_arrlst	chrlst;

	argument_builder_debug(0);
	while (1)
	{
		arg_builder_initialize(&chrlst);
		sub = 0;
		ret = eval_next(line, &sub, &chrlst);
		if (ret == 0 || ret == TOKEN_KIND_ARG_GROUP)
			arraylist_add(arglst, arg_builder_build(&chrlst));
		arg_builder_finalize(&chrlst);
		argument_builder_debug_new();
		line += sub;
		while (ft_iswspace(*line))
		{
			line++;
			sub++;
		}
		*consumed += sub;
		if (ret != TOKEN_KIND_ARG_GROUP)
			break ;
	}
	return (arglst->size == 0 && ret != 0 ? ret : TOKEN_KIND_ARG_GROUP);
}

static int
	handle(int kind, t_arrlst *tokenlst)
{
	int	ret;

	ret = 1;
	if (kind >= TOKEN_KIND_INPUT && kind <= TOKEN_KIND_APPEND)
	{
		arraylist_add(tokenlst, token_create_io_file(kind, NULL));
		ret += kind == TOKEN_KIND_APPEND;
	}
	else if (kind == TOKEN_KIND_PIPE)
		arraylist_add(tokenlst, token_create(TOKEN_KIND_PIPE, NULL));
	else if (kind == TOKEN_KIND_SEMICOLON)
	{
		arraylist_add(tokenlst, token_create(TOKEN_KIND_SEMICOLON, NULL));
		ret = 0;
	}
	return (ret);
}

int
	eval_tokens(t_arrlst *tokenlst, char *line, size_t *consumed)
{
	int			kind;
	size_t		sub;
	t_arrlst	*arglst;

	while (*line)
	{
		while (ft_iswspace(*line))
			eval_consume(1, &line, consumed, 0);
		arglst = arraylist_create(10, NULL);
		sub = 0;
		kind = next_token(arglst, line, &sub);
		eval_consume(sub + (kind == TOKEN_KIND_SEMICOLON), &line, consumed, 0);
		if (kind == TOKEN_KIND_ARG_GROUP)
			arraylist_add(tokenlst, token_create_arg_group(arglst, 1));
		else
		{
			arraylist_destroy(arglst);
			eval_consume(handle(kind, tokenlst), &line, consumed, 0);
			if (kind == TOKEN_KIND_SEMICOLON)
				return (1);
		}
	}
	return (0);
}
