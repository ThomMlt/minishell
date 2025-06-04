/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:38:51 by lidbaha           #+#    #+#             */
/*   Updated: 2025/03/29 06:16:09 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	clean_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	clean_t_redir(t_redir *redir)
{
	t_redir		*temp;

	temp = redir;
	while (temp != NULL)
	{
		free(temp->file);
		if (temp->next != NULL)
		{
			redir = temp->next;
			free(temp);
			temp = redir;
		}
		else
		{
			free(temp);
			break ;
		}
	}
}

void	clean_t_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		clean_split(cmd->args);
		if (cmd->infile != NULL)
			clean_t_redir(cmd->infile);
		if (cmd->outfile != NULL)
			clean_t_redir(cmd->outfile);
		free(cmd);
		cmd = tmp;
	}
}

void	clean_pipe(char **pipe)
{
	int	i;

	if (!pipe)
		return ;
	i = 0;
	while (pipe[i])
	{
		if (pipe[i] != NULL)
			free(pipe[i]);
		i++;
	}
	free(pipe);
}

void	clean_redir(t_parse_redir *redir)
{
	t_parse_redir	*temp;

	while (redir != NULL)
	{
		temp = redir;
		redir = redir->next;
		clean_split(temp->line);
		free(temp);
	}
}
