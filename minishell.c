/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:33:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:33:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_input_loop(t_minishell *shell, char **envp)
{
	char	*line;
	int		ret;

	while (1)
	{
		ft_printf("%s$ ", shell->name);
		ret = get_next_line(IN, &line);
		if (line != NULL && ft_strlen(line) != 0)
			minishell_evaluate(shell, line, envp);
		free(line);
		if (ret <= 0)
			break ;
	}
}
