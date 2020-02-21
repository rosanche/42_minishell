/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:22:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 15:22:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	eval_q_single(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		ret;
	size_t	sub;

	while (*line)
	{
		if (*line == '\\')
		{
			if (*(line + 1) == '\'')
			{
				arg_builder_add_char(chrlst, '\\', '\'');
				*consumed += 2;
				return (0);
			}
			else
			{
				ret = eval_escape_backslash(line, &sub);
				if (ret != -1)
				{
					arg_builder_add_char(chrlst, ret, '\'');
					*consumed += sub;
					line += *consumed;
				}
			}
		}
		else if (*line == '\'')
		{
			*consumed += 1;
			return (0);
		}
		else
			arg_builder_add_char(chrlst, *line, '\'');
		*consumed += 1;
		line++;
	}
	return (0);
}

int
	eval_q_double(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		ret;
	size_t	sub;

	while (*line)
	{
		if (*line == '\\')
		{
			if (*(line + 1) == '\"')
			{
				line++;
				arg_builder_add_char(chrlst, '\"', '\"');
				*consumed += 1;
			}
			else
			{
				ret = eval_escape_backslash(line, &sub);
				if (ret != -1)
				{
					arg_builder_add_char(chrlst, ret, '\"');
					*consumed += sub;
					line += sub;
				}
			}
		}
		else if (*line == '\"')
		{
			*consumed += 1;
			return (0);
		}
		else
			arg_builder_add_char(chrlst, *line, '\"');
		*consumed += 1;
		line++;
	}
	return (0);
}
