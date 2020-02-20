/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:33:00 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:33:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	kind_to_open_mode(int kind)
{
	if (kind == TOKEN_KIND_INPUT_FILE)
		return (O_RDONLY);
	if (kind == TOKEN_KIND_OUTPUT_FILE)
		return (O_WRONLY);
	if (kind == TOKEN_KIND_APPEND_FILE)
		return (O_APPEND);
	return (-1);
}

t_token
	*token_create_io_file(int kind, char *path)
{
	int				open_mode;
	t_token			*tok;
	t_token_io_file	*tok_io;

	open_mode = kind_to_open_mode(kind);
	if (open_mode == -1)
		return (NULL);
	if (!(tok_io = malloc(sizeof(t_token_io_file))))
		return (NULL);
	tok_io->open_mode = open_mode;
	tok_io->path = ft_strdup(path);
	if (!(tok = token_create(kind, tok_io)))
	{
		token_destroy_io_file(tok_io);
		return (NULL);
	}
	return (tok);
}

void
	token_destroy_io_file(t_token_io_file *tok_io)
{
	free(tok_io->path);
	free(tok_io);
}
