/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builder_io.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:46:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 14:46:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** ft_printf("OPEN MODE: %d\n", tok_io->open_mode);
*/

//static int
//	set_io_open_err(int kind, t_process *process, char *path)
//{
//	path = ft_strdup(path);
//	if (kind == TOKEN_KIND_INPUT)
//	{
//		process->in_file = path;
//		process->in_errno = errno;
//	}
//	else
//	{
//		process->out_file = path;
//		process->out_errno = errno;
//	}
//	return (EB_ERR_OPEN_FAIL);
//}
//
//static int
//	set_io(t_process *process, t_token *tok, t_token *next)
//{
//	t_token_io_file		*tok_io;
//	char				*str;
//	int					*to;
//
//	tok_io = (t_token_io_file *)(tok->value);
//	str = (char *)(next->value);
//	if (next->kind != TOKEN_KIND_STRING)
//		return (EB_ERR_INVALID_NEXT);
//	tok_io->path = str;
//	to = tok->kind == TOKEN_KIND_INPUT ? &(process->in_fd) : &(process->out_fd);
//	if (*to != -1)
//		close(*to);
//	*to = open(tok_io->path, tok_io->open_mode, 0644);
//	if (*to == -1)
//		return (set_io_open_err(tok->kind, process, tok_io->path));
//	return (0);
//}
//
//int
//	executor_builder_io_set(t_process *process, t_token *tok, t_token *next)
//{
//	return ((process->b_err = set_io(process, tok, next)));
//}
