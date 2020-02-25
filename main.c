/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:18:34 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:18:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main0(int argc, char **argv)
{
	int			ret;
	int			fd;
	t_mshell	shell;
	size_t		index;
	t_arrlst	*tokenlst;
	size_t		sub;
	t_token		*tok;
	int			kind;
	char		*line;
	char		*xline;

	minishell_initialize(&shell, argv[0]);
	fd = open("/dev/stdin", O_RDONLY);
	while (1)
	{
		get_next_line(fd, &line);
		xline = line;
		while (*line != '\0')
		{
			ft_printf("++++++++++++++++ %s\n", line);
			tokenlst = arraylist_create(10, NULL);
			sub = 0;
			eval_tokens(tokenlst, line, &sub);
			for (index = 0; index < tokenlst->size; index++)
			{
				tok = (t_token *)tokenlst->items[index];
				kind = tok->kind;
				ft_printf("kind: %d %s\n", kind, (char *[]){
						"--",
						"STRING",
						"INPUT_FILE",
						"OUTPUT_FILE",
						"APPEND_FILE",
						"PIPE",
						"SEMICOLON",
						"++"
				}[kind]);
				if (kind == TOKEN_KIND_STRING)
					ft_printf("\t- '%s'\n", tok->value);
			}
			line += sub;
			ft_printf("-------------- sub %d, %s -- size = %d\n", 0 + sub, line, tokenlst->size);


			size_t	index = 0;
			t_arrlst *processlst = arraylist_create(10, NULL);
			ft_printf("ret: %s (errno = %d, str = %s)\n", (char *[]){
					"No error.",
					EB_ERR_NO_NEXT_T,
					EB_ERR_SYNTAX_T,
					EB_ERR_EMPTY_NEXT_T,
					"Failed to open.",
					EB_ERR_NO_NAME_T
			}[executor_builder(&index, tokenlst, processlst)], errno, strerror(errno));
			process_print_struct_arrlst(processlst);
			arraylist_clear(processlst, &process_destroy);
			arraylist_destroy(processlst);




			arraylist_clear(tokenlst, &token_destroy_sub);
			arraylist_destroy(tokenlst);
		}
		free(xline);
	}
	return (EXIT_SUCCESS);
}

int
	main(int argc, char **argv, char **envp)
{
	t_mshell	shell;

	minishell_signals_attach();
	env_initialize(envp);
	minishell_initialize(&shell, argv[0]);
	minishell_pre_loop(&shell);
	minishell_input_loop(&shell);
	return (EXIT_SUCCESS);
}
