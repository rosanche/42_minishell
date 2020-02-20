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
# include <signal.h>

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
# define ERR_NOT_VALID_ID "not a valid identifier"

# define INVALID 1

# define BASE_HOME_DIRECTORY "/Users/"

typedef struct	s_minishell
{
	char	*name;
	char	last_code;
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

int				g_flag_in_read;

t_builtin		g_builtin[BUILTIN_COUNT];

t_minishell		*g_shell;

void			minishell_initialize(t_minishell *shell, char *name);
void			minishell_pre_loop(t_minishell *shell);
void			minishell_input_loop(t_minishell *shell);

void			minishell_evaluate(t_minishell *shell, char *line);
void			minishell_evaluate_argument(t_arrlst *arglst, char *line);
int				minishell_evaluate_builtin(t_minishell *shell, t_arrlst *arglst);

void			minishell_error(t_minishell *shell, char *exec, char *error);
void			minishell_exit(t_minishell *shell, char code);

void			minishell_prompt_ask(t_minishell *shell, int with_new_line);

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

int				env_var_is_name_valid(char *name, int allow_equal);

int				env_set_from_line(char *line);
void			env_set(t_env_var *var);

void			env_unset_from_name(char *name);

t_env_var		*env_get_by_name(char *name);

void			env_var_free(t_env_var *var);
void			env_var_free_and_release(t_env_var **var);

void			env_finalize(void);

void			env_dump_content(void);

int				env_compare_by_name(t_env_var *item, char *to);

char			**env_array_get(t_minishell *shell);
void			env_array_build(t_minishell *shell);
void			env_array_invalidate(void);

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


size_t			evaluate_quote_size(char *line, size_t *consumed);
int				evaluator_escape_backslash(char *seq, size_t *consumed);

int				evaluate_next(char *line, size_t *consumed, t_arrlst *chrlst);
int				evaluate_quote_single(char *line, size_t *consumed, t_arrlst *chrlst);
int				evaluate_quote_double(char *line, size_t *consumed, t_arrlst *chrlst);

int				evaluate_tilde(char *line, size_t *consumed, t_arrlst *chrlst);

void			argument_builder_initialize(t_arrlst *chrlst);
void			argument_builder_finalize(t_arrlst *chrlst);
void			argument_builder_add_char(t_arrlst *chrlst, char chr, char quote);
char			*argument_builder_build(t_arrlst *chrlst);

int				g_argument_builder_debug;

void			argument_builder_debug(int state);
void			argument_builder_debug_print_char(char chr, char quote);
void			argument_builder_debug_new(void);

int				minishell_signals_attach(void);

int				g_signal_interrupt;
int				g_signal_quit;

void			signal_handler_interrupt(int sig);
void			signal_handler_quit(int sig);

int				signal_has_interrupt(int and_reset);
int				signal_has_quit(int and_reset);

# define TOKEN_KIND_ARG_GROUP 1
# define TOKEN_KIND_INPUT_FILE 2
# define TOKEN_KIND_OUTPUT_FILE 3
# define TOKEN_KIND_APPEND_FILE 4
# define TOKEN_KIND_PIPE 5

typedef struct	s_token
{
	int			kind;
	void		*value;
}				t_token;

typedef struct	s_token_arg_group
{
	int			auto_free;
	t_arrlst	*arglst;
}				t_token_arg_group;

typedef struct	s_token_io_file
{
	int		open_mode;
	char	*path;
}				t_token_io_file;

void			evaluate_tokens(t_arrlst *tokenlst, char *line, size_t *consumed);

t_token			*token_create(int kind, void *value);
void			token_destroy(t_token *tok, int sub_free);

t_token			*token_create_arg_group(t_arrlst *arglst, int auto_free);
void			token_destroy_arg_group(t_token_arg_group *tok_arg);

t_token			*token_create_io_file(int kind, char *path);
void			token_destroy_io_file(t_token_io_file *tok_io);

char			*utility_find_home_dir(void);

#endif
