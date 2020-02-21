/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:16:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 12:16:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell2.h"

void
	minishell_evaluate(t_mshell *shell, char *line)
{
	t_arrlst	arglst;
	char		*name;

	int			ret;

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
//	arraylist_init(&arglst, NULL, 5);
//	minishell_evaluate_argument(&arglst, line);
//	arraylist_add(&arglst, NULL);
//	name = arglst.items[0];
//	if (!minishell_evaluate_builtin(shell, &arglst))
//		if (!exec(name, env_array_get(shell), (char **)arglst.items))
//			minishell_error(shell, name, ERR_CMD_NOT_FOUND);
//	arraylist_clear(&arglst, &free);
//	arraylist_destroy_items(&arglst);
}
