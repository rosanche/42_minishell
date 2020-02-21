/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:19:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 12:19:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process
	*new(void)
{
	t_process	*process;

	if (!(process = malloc(sizeof(t_process))))
		return (NULL);
	ft_memset(process, 0, sizeof(t_process));
	process->in_fd = -1;
	process->out_fd = -1;
	return (process);
}

static void
	builder_io(t_process *process, t_arrlst *toklst, size_t *index)
{
	t_token		*tok;
	t_token		*next;

	tok = toklst->items[*index];
	if (!(process->b_err = toklst->size - *index == 1 ? EB_ERR_NO_NEXT : 0))
	{
		next = toklst->items[*index + 1];
		executor_builder_io_set(process, tok, next);
		*index += 1;
	}
}

static t_process
	*single(t_arrlst *toklst, size_t *index)
{
	t_process	*process;
	t_token		*tok;
	int			kind;

	if (*index >= toklst->size || !(process = new()))
		return (NULL);
	if (!(process->arglst = arraylist_create(10, NULL)))
	{
		free(process);
		return (NULL);
	}
	while (*index < toklst->size)
	{
		tok = toklst->items[*index];
//		ft_printf("kind %d\n", tok->kind);
		if ((kind = tok->kind) == TOKEN_KIND_ARG_GROUP)
			executor_builder_arg_add(process, tok);
		else if (kind >= TOKEN_KIND_INPUT && kind <= TOKEN_KIND_APPEND)
			builder_io(process, toklst, index);
		else if (kind == TOKEN_KIND_PIPE)
			break ;
		if (process->b_err)
			break ;
		*index += 1;
	}
	return (process);
}

// cat < x > y
// cat > x < y

void
	executor_builder(t_arrlst *toklst, t_arrlst *processlst)
{
	size_t		index;
	t_process	*pr;

	index = 0;
	while (1)
	{
		if (!(pr = single(toklst, &index)))
			break ;
		if (pr->b_err != 0)
		{
			if (pr->b_err == EB_ERR_NO_NEXT)
				minishell_error_simple(g_shell, EB_ERR_NO_NEXT_T);
			else if (pr->b_err == EB_ERR_INVALID_NEXT)
				minishell_error_simple(g_shell, EB_ERR_INVALID_NEXT_T);
			else if (pr->b_err == EB_ERR_EMPTY_NEXT)
				minishell_error_simple(g_shell, EB_ERR_EMPTY_NEXT_T);
			else if (pr->b_err == EB_ERR_OPEN_FAIL)
			{
				if (pr->in_errno != 0)
					minishell_error_file(g_shell, pr->in_file, pr->in_errno);
				else if (pr->out_errno != 0)
					minishell_error_file(g_shell, pr->out_file, pr->out_errno);
			}
		}
		arraylist_add(processlst, pr);
		index++;
	}
}
