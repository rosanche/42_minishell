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

static char
	*builtin_handler_cd_get_home_dir(void)
{
	t_env_var	*var;

	var = env_get_by_name("HOME");
	if (var != NULL)
		return (ft_strdup(var->value));
	var = env_get_by_name("USER");
	if (var == NULL)
		var = env_get_by_name("LOGNAME");
	if (var != NULL)
		return (ft_strjoin(BASE_HOME_DIRECTORY, var->value));
	return (ft_strdup("~"));
}

void
	builtin_handler_cd(t_minishell *shell, t_builtin_param param)
{
	char	*path;

	if (param.argc == 1)
		path = builtin_handler_cd_get_home_dir();
	else
		path = param.argv[1];
	if (chdir(path) == -1)
		builtin_errno(shell, param, path);
	if (param.argc == 1)
		free(path);
}
