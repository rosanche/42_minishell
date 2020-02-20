/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:22:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 15:22:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	argument_builder_initialize(t_arrlst *chrlst)
{
	arraylist_init(chrlst, NULL, 100);
	arraylist_grow(chrlst, 100);
}

void
	argument_builder_finalize(t_arrlst *chrlst)
{
	arraylist_destroy_items(chrlst);
}

void
	argument_builder_add_char(t_arrlst *chrlst, char chr, char quote)
{
	arraylist_add(chrlst, (void *)((long)0 + chr));
	argument_builder_debug_print_char(chr, quote);
}

char
	*argument_builder_build(t_arrlst *chrlst)
{
	char	*arg;
	size_t	index;

	if (!(arg = malloc(chrlst->size)))
		return (NULL);
	index = 0;
	while (index < chrlst->size)
	{
		arg[index] = (char)(0 + chrlst->items[index]);
		index++;
	}
	arg[index] = '\0';
	return (arg);
}
