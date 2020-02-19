/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_index_of.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:33:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 13:33:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

ssize_t
	arraylist_index_of(t_arrlst *alst, void *ptr)
{
	ssize_t	index;

	if (alst == NULL || alst->cmp_method == NULL
		|| alst->items == NULL || alst->size == 0)
		return (-2);
	index = 0;
	while (index < alst->size)
	{
		if ((*(alst->cmp_method))(alst->items[index], ptr) == 0)
			return (index);
		index++;
	}
	return (-1);
}
