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
	builtin_error(t_minishell *shell, t_builtin_param param,
					char *arg, char *error)
{
	if (error == NULL)
		error = "error";

	if (arg == NULL)
	{
		ft_dprintf(param.fd_err, "%s: %s: %s\n",
					shell->name, param.name, error);
	}
	else
	{
		ft_dprintf(param.fd_err, "%s: %s: %s: %s\n",
					shell->name, param.name, arg, error);
	}
}

void
	builtin_errno(t_minishell *shell, t_builtin_param param, char *arg)
{
	builtin_error(shell, param, arg, strerror(errno));
	errno = 0;
}
