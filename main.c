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

/*
** -fsanitize=address
*/

int
	main3(int argc, char **argv)
{
	t_arrlst	*alst;

	alst = arraylist_create(2, NULL);
	for (size_t i = 0; i < 15; i++)
		arraylist_add(alst, (void*)i);
	arraylist_add(alst, (void*)1);
	arraylist_add(alst, (void*)2);
	arraylist_add(alst, (void*)3);
	for (size_t i = 0; i < alst->size; i++)
		ft_printf("[%5d] = %d\n", (int)i, (int)(alst->items[i]));
	ft_printf("--------\n");
	for (size_t i = 6; i < 9; i++)
		arraylist_remove_at(alst, 6, NULL);
	for (size_t i = 0; i < alst->size; i++)
		ft_printf("[%5d] = %d\n", (int)i, (int)(alst->items[i]));
	arraylist_destroy(alst);
	return (EXIT_SUCCESS);
}

int
	main4(int argc, char **argv)
{
	t_mshell	shell;

	ft_printf("SHELLING %s\n", shell.name);

	ft_printf("--- %d\n", ft_is_base_valid(BASE_HEX_LOW));

	size_t a = 0;
	int ret = 0;
	printf("at start %lu\n", a);

	ft_printf("\n\n\n\n");

	char *str;
	//	str = "Hello World 'from quotes' end, and now with_escaped '\\'' \"\\x65\\\" \"\\x65\" how is it ? alone= \\' so? --<";
//	str = "Hello World 'from \"quotes\"' end, now \"here are the doubles and escaped \\\"  \", ANDDDD 'the singlet '\"'\"' escaped quote '";
//	str = "\\\"\\ \\\"";
//	str = "\\\"";
//	str = "\\\'";
	str = "\' \\\' \\\" \\x66 x\'";
//	str = "' \\' '";
//	while (1)
//	{
//		ft_printf(">..");
//		ret = evaluate_quote(str, 0, &a);
//		ft_printf("..");
//		ft_printf(":%d\n", ((int)(0 + a)));
//		str += a;
//		while (ft_iswspace(*str))
//			str++;
//		a = 0;
//		if (!ret)
//			break ;
//	}
	ft_printf("\n\n\n\n");
	return (EXIT_SUCCESS);
}

int
	main0(int argc, char **argv)
{
	int			ret;

	char *line = "echo Hello 'World From' \"Quo otes\" | cat -e> 'hello'>>;   asd asd asd asd ";
	while (1)
	{
		ft_printf("++++++++++++++++ %s\n", line);
		t_arrlst	*tokenlst = arraylist_create(10, NULL);
		size_t		sub = 0;
		ret = eval_tokens(tokenlst, line, &sub);
		//ft_printf("ret %d, sub %d\n", ret, 0 + sub);
		for (size_t index = 0; index < tokenlst->size; index++)
		{
			t_token *tok = (t_token *)tokenlst->items[index];
			int kind = tok->kind;
			ft_printf("kind: %d %s\n", kind, (char *[]){
					"--",
					"ARG_GROUP",
					"INPUT_FILE",
					"OUTPUT_FILE",
					"APPEND_FILE",
					"PIPE",
					"SEMICOLON",
					"++"
			}[kind]);
			if (kind == TOKEN_KIND_ARG_GROUP)
			{
				t_arrlst *arglst = ((t_token_arg_group *)tok->value)->arglst;
				for (size_t jndex = 0; jndex < arglst->size; jndex++)
				{
					ft_printf("\t- '%s'\n", arglst->items[jndex]);
				}
			}
		}
		if (!ret)
			break ;
		line += sub;
		ft_printf("-------------- sub %d, %s\n", 0 + sub, line);
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
