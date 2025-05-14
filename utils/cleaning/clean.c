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

void	free_tab(char **tab, int y)
{
	while (y >= 0)
		free(tab[y--]);
	free(tab);
}

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

void	clean_quotes(t_quotes *quotes)
{
	while (quotes->next != NULL)
	{
		free(quotes->line);
		quotes = quotes->next;
	}
	free(quotes);
}

void	clean_cmd(t_parse *cmd)
{
	clean_split(cmd->space->line);
	clean_split(cmd->pipe->line);
	clean_split(cmd->redir_input->line);
	clean_split(cmd->redir_output->line);
	clean_split(cmd->redir_append->line);
	clean_split(cmd->redir_heredoc->line);
	if (cmd->line)
		free(cmd->line);
	if (cmd->space)
		free(cmd->space);
	if (cmd->pipe)
		free(cmd->pipe);
	if (cmd->redir_input)
		free(cmd->redir_input);
	if (cmd->redir_output)
		free(cmd->redir_output);
	if (cmd->redir_append)
		free(cmd->redir_append);
	if (cmd->redir_heredoc)
		free(cmd->redir_heredoc);
	free(cmd);
}

void	clean_env(void)
{
	clear_history();
	rl_clear_signals();
	rl_cleanup_after_signal();
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