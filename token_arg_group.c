/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_arg_group.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:33:00 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:33:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token
	*token_create_arg_group(t_arrlst *arglst, int auto_free)
{
	t_token				*tok;
	t_token_arg_group	*tok_arg;

	if (!(tok_arg = malloc(sizeof(t_token_arg_group))))
		return (NULL);
	tok_arg->auto_free = auto_free;
	tok_arg->arglst = arglst;
	if (!(tok = token_create(TOKEN_KIND_ARG_GROUP, tok_arg)))
	{
		token_destroy_arg_group(tok_arg);
		return (NULL);
	}
	return (tok);
}

void
	token_destroy_arg_group(t_token_arg_group *tok_arg)
{
	if (tok_arg->auto_free)
	{
		arraylist_clear(tok_arg->arglst, &free);
		arraylist_destroy(tok_arg->arglst);
	}
	free(tok_arg);
}
