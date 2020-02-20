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

# define BIN_ECHO "echo"
# define BIN_CD "cd"
# define BIN_PWD "pwd"
# define BIN_EXPORT "export"
# define BIN_UNSET "unset"
# define BIN_ENV "env"
# define BIN_EXIT "exit"

# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NUM_ARG_REQ "numeric argument required"

# define BASE_HOME_DIRECTORY "/Users/"

typedef struct	s_minishell
{
	char	*name;
}				t_minishell;

typedef struct	s_builtin_param
{
	char	*name;
	int		argc;
	char	**argv;
	int		fd_out;
	int		fd_err;
}				t_builtin_param;

typedef void	(*t_builtin_handler)(t_minishell *, t_builtin_param);

typedef struct	s_builtin
{
	t_builtin_handler	handler;
	char				*name;
}				t_builtin;

t_builtin		g_builtin[BUILTIN_COUNT];

void			minishell_initialize(t_minishell *shell, char *name);
void			minishell_pre_loop(t_minishell *shell);
void			minishell_input_loop(t_minishell *shell,char **envp);

void			minishell_evaluate(t_minishell *shell, char *line, char **envp);

void			minishell_error(t_minishell *shell, char *exec, char *error);
void			minishell_exit(t_minishell *shell, char code);

t_builtin		*builtin_match(char *name);

void			builtin_error(t_minishell *shell, t_builtin_param param, char *arg, char *error);
void			builtin_errno(t_minishell *shell, t_builtin_param param, char *arg);

void			builtin_handler_echo(t_minishell *shell, t_builtin_param param);
void			builtin_handler_cd(t_minishell *shell, t_builtin_param param);
void			builtin_handler_pwd(t_minishell *shell, t_builtin_param param);
void			builtin_handler_export(t_minishell *shell, t_builtin_param param);
void			builtin_handler_unset(t_minishell *shell, t_builtin_param param);
void			builtin_handler_env(t_minishell *shell, t_builtin_param param);
void			builtin_handler_exit(t_minishell *shell, t_builtin_param param);

typedef struct	s_env_var
{
	char	*name;
	char	*value;
}				t_env_var;

t_arrlst		g_env_variables;

void			env_initialize(char **envp);
int				env_load(char **envp);

t_env_var		*env_var_create_from_line(char *line);
t_env_var		*env_var_create(char *name, char *value);

void			env_set_from_line(char *line);
void			env_set(t_env_var *var);

void			env_unset_from_name(char *name);

t_env_var		*env_get_by_name(char *name);

void			env_var_free(t_env_var *var);
void			env_var_free_and_release(t_env_var **var);

void			env_finalize(void);

void			env_dump_content(void);

int				env_compare_by_name(t_env_var *item, char *to);

typedef struct	s_quote_ctx
{
	char	type;
	int		in;
}				t_quote_ctx;

typedef struct	s_cmd_group
{
	size_t	pos;
	char	*line;
}				t_cmd_group;


int				evaluate_quote(char *line, char of, size_t *consumed);
size_t			evaluate_quote_size(char *line, size_t *consumed);
int				evaluator_escape_backslash(char *seq, size_t *consumed);

#endif
