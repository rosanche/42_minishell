/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:32:51 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 16:32:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_error(t_minishell *shell, char *exec, char *arg, char *error)
{
	if (error == NULL)
		error = "error";

	if (arg == NULL)
		ft_dprintf(ERR, "%s: %s: %s\n", shell->name, exec, error);
	else
		ft_dprintf(ERR, "%s: %s: %s: %s\n", shell->name, exec, arg, error);
}

void
	builtin_errno(t_minishell *shell, char *exec, char *arg)
{
	builtin_error(shell, exec, arg, strerror(errno));
	errno = 0;
}
