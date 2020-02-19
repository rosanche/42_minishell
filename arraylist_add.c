/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:29:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 18:29:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_add(t_arrlst *alst, void *ptr)
{
	if (!arraylist_grow(alst, 1))
		return (0);
	alst->items[alst->size] = ptr;
	alst->size++;
	return (1);
}
