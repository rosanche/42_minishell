/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_destroy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:43:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 17:43:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	process_destroy(t_process *process)
{
	free(process->name);
	arraylist_clear(process->arglst, free);
	arraylist_destroy(process->arglst);
	free(process);
}
