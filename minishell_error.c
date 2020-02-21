/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:22:58 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 17:22:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_error(t_mshell *shell, char *exec, char *error)
{
	if (error == NULL)
		error = "error";
	ft_dprintf(ERR, "%s: %s: %s\n", shell->name, exec, error);
}
