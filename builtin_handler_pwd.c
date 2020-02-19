/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:22:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:22:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_handler_pwd(t_minishell *shell, int argc, char **argv)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, OUT);
	free(path);
}
