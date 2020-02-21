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

static int
	minishell_evaluate_next_tokens(t_arrlst **tokenlst, size_t *sub, char *line)
{
	if (!(*tokenlst = arraylist_create(10, NULL)))
		return (NULL);
	return (eval_tokens(*tokenlst, line, &sub));
}

static void
	minishell_execute_process(t_mshell *shell, t_arrlst *processlst)
{
	t_process	*process;

	while (processlst->size != 0)
	{
		process = (t_process *)processlst->items[0];
		if (process == NULL)
			break ;
//		process_print_struct(process);
		arraylist_add(process->arglst, NULL);
		process->name = process->arglst->items[0];
		process->name = process->name == NULL ? NULL : ft_strdup(process->name);
		if (process->b_err == 0)
		{
			if (minishell_evaluate_builtin(shell, process))
				;
			else if (process_find_path(process))
				process_execute(process);
			else
				minishell_error(shell, process->name, ERR_CMD_NOT_FOUND);
		}
		arraylist_remove_at(processlst, 0, &process_destroy);
	}
}

void
	minishell_evaluate(t_mshell *shell, char *line)
{
	t_arrlst	*processlst;
	size_t		sub;
	t_arrlst	*tokenlst;
	int			ret;

	while (1)
	{
		sub = 0;
		ret = minishell_evaluate_next_tokens(&tokenlst, &sub, line);
		processlst = arraylist_create(5, NULL);
		executor_builder(tokenlst, processlst);
		minishell_execute_process(shell, processlst);
		arraylist_destroy(processlst);
		arraylist_clear(tokenlst, &token_destroy_sub);
		arraylist_destroy(tokenlst);
		line += sub;
		if (*line == '\0' || !ret)
			break ;
	}
}
