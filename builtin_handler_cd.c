/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_cd(t_minishell *shell, int argc, char **argv)
{
	char	*path;

	if (argc == 1)
		path = "~";
	else
		path = argv[1];
	if (chdir(path) == -1)
		builtin_errno(shell, "cd", path);
}
