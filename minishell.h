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
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "ft_printf/ft_printf.h"

# include "arraylist.h"

# define ENV_FILE_PATH "env.txt"
# define BUILTIN_COUNT 7

# define DISPLAY_LOADED_VARS 1
# define INTERRUPT_DOES_EXIT 1

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
# define ERR_UNEXPECTED "unexpected syntax"
# define ERR_FORK_FAILED "failed to fork()"

# define INVALID 1

# define BASE_HOME_DIRECTORY "/Users/"

typedef struct	s_minishell
{
	char		*name;
	int			last_code;
	t_arrlst	*pidlst;
}				t_mshell;

typedef struct	s_builtin_param
{
	char	*name;
	int		argc;
	char	**argv;
	int		fd_out;
	int		fd_err;
}				t_builtin_param;

typedef void	(*t_builtin_handler)(t_mshell *, t_builtin_param);

typedef struct	s_builtin
{
	t_builtin_handler	handler;
	char				*name;
}				t_builtin;

int				g_flag_in_read;

t_builtin		g_builtin[BUILTIN_COUNT];

t_mshell		*g_shell;

void			minishell_initialize(t_mshell *shell, char *name);
void			minishell_pre_loop(t_mshell *shell);
void			minishell_input_loop(t_mshell *shell);

void			minishell_evaluate(t_mshell *shell, char *line);
void			minishell_evaluate_argument(t_arrlst *arglst, char *line);

void			minishell_error(t_mshell *shell, char *exec, char *error);
void			minishell_exit(t_mshell *shell, char code);

void			minishell_prompt_ask(t_mshell *shell, int with_new_line);

t_builtin		*builtin_match(char *name);

void			builtin_error(t_mshell *s, t_builtin_param p, char *a, char *e);
void			builtin_errno(t_mshell *s, t_builtin_param p, char *a);

void			builtin_handler_echo(t_mshell *shell, t_builtin_param param);
void			builtin_handler_cd(t_mshell *shell, t_builtin_param param);
void			builtin_handler_pwd(t_mshell *shell, t_builtin_param param);
void			builtin_handler_export(t_mshell *shell, t_builtin_param param);
void			builtin_handler_unset(t_mshell *shell, t_builtin_param param);
void			builtin_handler_env(t_mshell *shell, t_builtin_param param);
void			builtin_handler_exit(t_mshell *shell, t_builtin_param param);

typedef struct	s_env_var
{
	char	*name;
	size_t	name_len;
	char	*value;
}				t_env_var;

t_arrlst		g_env_variables;

void			env_initialize(char **envp);
int				env_load(char **envp);

t_env_var		*env_var_create_from_line(char *line);
t_env_var		*env_var_create(char *name, char *value);

int				env_var_is_name_valid(char *name, int allow_equal);
int				env_var_is_name_valid_len(char *name, int allow_equal);

int				env_set_from_line(char *line);
void			env_set(t_env_var *var);

void			env_unset_from_name(char *name);

t_env_var		*env_get_by_name(char *name);

void			env_var_free(t_env_var *var);
void			env_var_free_and_release(t_env_var **var);

void			env_finalize(void);

void			env_dump_content(void);

int				env_compare_by_name(t_env_var *item, char *to);

char			**env_array_get(void);
void			env_array_build(void);
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

int				eval_next(char *line, size_t *consumed, t_arrlst *chrlst);
int				eval_q_single(char *line, size_t *consumed, t_arrlst *chrlst);
int				eval_q_double(char *line, size_t *consumed, t_arrlst *chrlst);
int				eval_tilde(char *line, size_t *consumed, t_arrlst *chrlst);
int				eval_env_var(char *line, size_t *consumed, t_arrlst *chrlst);
int				eval_tokens(t_arrlst *tokenlst, char *line, size_t *consumed);
int				eval_escape_backslash(char *seq, size_t *consumed);

int				eval_consume(size_t sub, char **line, size_t *consumed, int r);

void			arg_builder_initialize(t_arrlst *chrlst);
void			arg_builder_finalize(t_arrlst *chrlst);
void			arg_builder_add_char(t_arrlst *chrlst, char chr, char quote);
void			arg_builder_add_string(t_arrlst *chrlst, char *str, char quote);
char			*arg_builder_build(t_arrlst *chrlst);

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
# define TOKEN_KIND_INPUT 2
# define TOKEN_KIND_OUTPUT 3
# define TOKEN_KIND_APPEND 4
# define TOKEN_KIND_PIPE 5
# define TOKEN_KIND_SEMICOLON 6

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

t_token			*token_create(int kind, void *value);
void			token_destroy(t_token *tok, int sub_free);
void			token_destroy_sub(t_token *tok);

t_token			*token_create_arg_group(t_arrlst *arglst, int auto_free);
void			token_destroy_arg_group(t_token_arg_group *tok_arg);

t_token			*token_create_io_file(int kind, char *path);
void			token_destroy_io_file(t_token_io_file *tok_io);

char			*utility_find_home_dir(void);

# define EB_ERR_NO_NEXT 1
# define EB_ERR_INVALID_NEXT 2
# define EB_ERR_EMPTY_NEXT 3
# define EB_ERR_OPEN_FAIL 4

# define EB_ERR_NO_NEXT_T "No file after operator."
# define EB_ERR_INVALID_NEXT_T "Invalid syntax combinaison."
# define EB_ERR_EMPTY_NEXT_T "File name empty."

typedef struct	s_process
{
	char		*name;
	char		*filepath;
	int			is_dir;
	t_arrlst	*arglst;
	int			in_fd;
	char		*in_file;
	int			in_errno;
	int			out_fd;
	char		*out_file;
	int			out_errno;
	int			b_err;
	pid_t		pid;
}				t_process;

int				process_find_path(t_process *process);
void			process_execute(t_process *process);
void			executor_builder(t_arrlst *toklst, t_arrlst *processlst);

void			process_destroy(t_process *process);

#endif
