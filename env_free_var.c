/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:04:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 19:04:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	env_free_var(t_env_var *var)
{
	ft_free_and_release((void **)(&(var->name)));
	ft_free_and_release((void **)(&(var->value)));
	ft_free_and_release((void **)(&var));
}
