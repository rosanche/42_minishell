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
	is_quote(int c)
{
	return (c == '\"' || c == '\'');
}

int
	evaluate_quote_single(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		ret;
	size_t	sub;

	while (*line)
	{
		if (*line == '\\')
		{
			if (*(line + 1) == '\'')
			{
				argument_builder_add_char(chrlst, '\\', '\'');
				*consumed += 2;
				return (0);
			}
			else
			{
				ret = evaluator_escape_backslash(line, &sub);
				if (ret != -1)
				{
					argument_builder_add_char(chrlst, ret, '\'');
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
			argument_builder_add_char(chrlst, *line, '\'');
		*consumed += 1;
		line++;
	}
	return (0);
}

int
	evaluate_quote_double(char *line, size_t *consumed, t_arrlst *chrlst)
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
				argument_builder_add_char(chrlst, '\"', '\"');
				*consumed += 1;
			}
			else
			{
				ret = evaluator_escape_backslash(line, &sub);
				if (ret != -1)
				{
					argument_builder_add_char(chrlst, ret, '\"');
					*consumed += sub;
					line += *consumed;
				}
			}
		}
		else if (*line == '\"')
		{
			*consumed += 1;
			return (0);
		}
		else
			argument_builder_add_char(chrlst, *line, '\"');
		*consumed += 1;
		line++;
	}
	return (0);
}

int
	evaluate_quote(char *line, size_t *consumed, t_arrlst *chrlst)
{
	int		ret;
	size_t	sub;

	while (*line)
	{
		if (*line == '\\')
		{
			if (is_quote(*(line + 1)))
			{
				argument_builder_add_char(chrlst, *(line + 1), 0);
				line += 2;
				*consumed += 2;
			}
			else
			{
				line += 1;
				*consumed += 1;
			}
		}
		else if (*line == '\'')
		{
			sub = 0;
			evaluate_quote_single(line + 1, &sub, chrlst);
			*consumed += sub + 1;
			line += sub + 1;
		}
		else if (*line == '\"')
		{
			sub = 0;
			evaluate_quote_double(line + 1, &sub, chrlst);
			*consumed += sub + 1;
			line += sub + 1;
		}
		else if (ft_iswspace(*line))
			return (1);
		else
		{
			argument_builder_add_char(chrlst, *line, 0);
			*consumed += 1;
			line++;
		}
	}
	return (0);
}

