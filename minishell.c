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
	minishell_input_loop(t_minishell *shell)
{
	char	*line;
	int		ret;

	while (1)
	{
		ft_printf("%s$ ", shell->name);
		ret = get_next_line(IN, &line);
		if (line != NULL && ft_strlen(line) != 0)
			minishell_handle(shell, line);
		free(line);
		if (ret <= 0)
			break ;
	}
}

void
	minishell_handle(t_minishell *shell, char *line)
{
	char		**split;
	t_builtin	*builtin;

	split = ft_split(line, ' ');
	builtin = builtin_match(split[0]);
	if (builtin)
		(*(builtin->handler))(shell, ft_split_length(split), split);
	else
		minishell_error(shell, split[0], "command not found");
	ft_split_free(&split);
}
