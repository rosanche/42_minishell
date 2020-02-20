/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:26:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:26:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token
	*token_create(int kind, void *value)
{
	t_token	*tok;

	if (!(tok = malloc(sizeof(t_token))))
		return (NULL);
	tok->kind = kind;
	tok->value = value;
	return (tok);
}

void
	token_destroy(t_token *tok, int sub_free)
{
	if (sub_free)
	{
		if (tok->kind == TOKEN_KIND_ARG_GROUP)
			token_destroy_arg_group(tok->value);
	}
	free(tok);
}
