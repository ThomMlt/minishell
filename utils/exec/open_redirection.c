/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:25:36 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/20 21:35:54 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		if (access(file, R_OK) == -1)
			permission_denied(file);
		else if (access(file, F_OK) == -1)
			no_such_file_or_directory(file);
		else
			error_message(file);
	}
	return (fd);
}

int	last_infile(t_cmd *cmd)
{
	int			fd;
	int			prev;
	t_redir		*infile;

	infile = cmd->infile;
	prev = -1;
	while (infile)
	{
		fd = open_infile(infile->file);
		if (prev != -1)
			close(prev);
		if (fd == -1)
			break ;
		prev = fd;
		infile = infile->next;
	}
	return (fd);
}

static int	open_outfile(char *file, t_token_type mode)
{
	int	fd;

	if (mode == REDIRECT_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		if (access(file, W_OK) == -1)
			permission_denied(file);
		else
			error_message(file);
	}
	return (fd);
}

int	last_outfile(t_cmd *cmd)
{
	int			fd;
	int			prev;
	t_redir		*outfile;

	outfile = cmd->outfile;
	prev = -1;
	while (outfile)
	{
		fd = open_outfile(outfile->file, outfile->type);
		if (prev != -1)
			close(prev);
		if (fd == -1)
			break ;
		prev = fd;
		outfile = outfile->next;
	}
	return (fd);
}

/* attention le break ne suffit pas ici */