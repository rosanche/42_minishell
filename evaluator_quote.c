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
	evaluate_quote(char *line, char of, size_t *consumed)
{
	int		ret;
	size_t	sub;

	while (*line)
	{
		//if (of == 0) { ft_printf("\e[96m%c\e[0m", *line); } else { ft_printf("\e[95m%c\e[0m", *line); }

		if (*line == '\\')
		{
			ft_printf("\e[96m");
			//ft_printf("%d/%d", of != 0, *(line + 1) == of);
			if (is_quote(*(line + 1)) && of == 0)
			{
				line++;
				ft_putchar_fd(*line, OUT);
				*consumed += 1;
			}
			else if (is_quote(*(line + 1)) && of == *(line + 1))
			{
				line++;
				ft_putchar_fd(*line, OUT);
				*consumed += 1;
			}
			else if (is_quote(*(line + 1)) && of != *(line + 1))
			{
				line++;
				ft_putchar_fd(*line, OUT);
				line++;
				ft_putchar_fd(*line, OUT);
				*consumed += 2;
			}
			else
			{
				//ft_printf(".");
				ret = evaluator_escape_backslash(line, &sub);
				if (ret != -1)
					ft_putchar_fd(ret, OUT);
//				ft_printf("r%d", (ret != -1 ? sub : 1));
				line += (ret != -1 ? sub : 0);
				*consumed += (ret != -1 ? sub : 1);
				//ft_printf(".%c.", *line);
			}
			ft_printf("\e[0m");
		}
		else if (*line == of)
		{
			ft_printf("\e[101mR\e[0m");
			return (0);
		}
		else if (of == 0 && (*line == '\'' || *line == '"'))
		{
			sub = 0;
			//ft_printf("\e[42m>\e[0m");
			ret = evaluate_quote(line + 1, *line, &sub);
			//ft_printf("\e[41m<%d,%d\e[0m", ret, sub + 1);
			*consumed += sub + 1;
			line += sub + 1;
			if (ret)
				return (1);
		}
		else if (ft_iswspace(*line) && of == 0)
			return (1);
		else
		{
			ft_putchar_fd(*line, OUT);
			*consumed += 1;
			line++;
		}
	}
	return (0);
}

size_t
	evaluate_quote_size(char *line, size_t *consumed)
{
	t_quote_ctx ctx;
	size_t		size;
	int			escaped;

	ctx = (t_quote_ctx){ 0, 0 };
	size = 0;
	while (*line)
	{
		if (*line == '\\')
		{
			escaped = evaluator_escape_backslash(line, consumed);
			if (escaped != -1)
			{
				ft_putchar_fd(escaped, OUT);
				line += *consumed;
			}
			else
			{
				ft_putchar_fd(*line, OUT);
				line += 1;
			}
		}
		else
		{
			ft_putchar_fd(*line, OUT);
			*consumed += !!++line;
		}
	}
	return (size);
}
