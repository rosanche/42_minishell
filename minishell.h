/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:15:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:15:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "ft_printf/ft_printf.h"

# include "arraylist.h"

# define ENV_FILE_PATH "env.txt"
# define BUILTIN_COUNT 7

# define DISPLAY_LOADED_VARS 1

typedef struct	s_minishell
{
	char	*name;
}				t_minishell;

typedef void	(*t_builtin_handler)(t_minishell *, int, char **);

typedef struct	s_builtin
{
	t_builtin_handler	handler;
	char				*name;
}				t_builtin;

t_builtin		g_builtin[BUILTIN_COUNT];

void			minishell_initialize(t_minishell *shell, char *name);
void			minishell_pre_loop(t_minishell *shell);
void			minishell_input_loop(t_minishell *shell);
void			minishell_handle(t_minishell *shell, char *line);

void			minishell_error(t_minishell *shell, char *exec, char *error);
void			minishell_exit(t_minishell *shell, char code);

t_builtin		*builtin_match(char *name);

void			builtin_error(t_minishell *shell, char *exec, char *arg, char *error);
void			builtin_errno(t_minishell *shell, char *exec, char *arg);

void			builtin_handler_echo(t_minishell *shell, int argc, char **argv);
void			builtin_handler_cd(t_minishell *shell, int argc, char **argv);
void			builtin_handler_pwd(t_minishell *shell, int argc, char **argv);
void			builtin_handler_exit(t_minishell *shell, int argc, char **argv);

typedef struct	s_env_var
{
	char		*name;
	char		*value;
}				t_env_var;

t_arrlst		g_env_variables;

void			env_initialize(char **envp);
int				env_load(char **envp);

void			env_set_from_line(char *line);
void			env_set(char *name, char *value);

void			env_free_var(t_env_var *var);

void			env_finalize(void);

void			env_dump_content(void);

#endif
