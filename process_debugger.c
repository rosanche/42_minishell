/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_debugger.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:02:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 16:02:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	process_print_struct(t_process *process)
{
	size_t	index;

	ft_printf("\n{\n");
	ft_printf("%20s : %s\n", "name", process->name);
	ft_printf("%20s : [\n", "arglst");
	index = 0;
	while (index < process->arglst->size)
	{
		ft_printf("\t\t\t%s,\n", process->arglst->items[index]);
		index++;
	}
	ft_printf("%20s]\n", "");
	ft_printf("%20s : %d\n", "in_fd", process->in_fd);
	ft_printf("%20s : %s\n", "in_file", process->in_file);
	ft_printf("%20s : %d\n", "in_errno", process->in_errno);
	ft_printf("%20s : %d\n", "out_fd", process->out_fd);
	ft_printf("%20s : %s\n", "out_file", process->out_file);
	ft_printf("%20s : %d\n", "out_errno", process->out_errno);
	ft_printf("%20s : %d\n", "builder_err", process->b_err);
	ft_printf("%20s : %d\n", "pid", 0 + process->pid);
	ft_printf("}\n");
}
