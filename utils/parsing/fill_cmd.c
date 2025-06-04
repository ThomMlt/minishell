/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:48:05 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/18 11:17:04 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

t_token_type	get_type(char *str)
{
	if (ft_strcmp_minishell(str, ">"))
		return (REDIRECT_OUT);
	if (ft_strcmp_minishell(str, "<"))
		return (REDIRECT_IN);
	if (ft_strcmp_minishell(str, ">>"))
		return (REDIRECT_APPEND);
	if (ft_strcmp_minishell(str, "<<"))
		return (HEREDOC);
	return (WORD);
}

void	add_split(t_cmd *current_cmd, char **split)
{
	int		i;
	int		index;
	char	**new;

	new = malloc(sizeof(char *)
			* (ft_split_len(split) + ft_split_len(current_cmd->args)));
	i = 0;
	index = 0;
	while (current_cmd->args[i] != NULL)
	{
		new[index] = ft_strdup(current_cmd->args[i]);
		index++;
		i++;
	}
	i = 1;
	while (split[i] != NULL)
	{
		new[index] = ft_strdup(split[i]);
		index++;
		i++;
	}
	new[index] = NULL;
	clean_split(current_cmd->args);
	current_cmd->args = ft_strdup_split(new);
	clean_split(new);
}

void	fill_line(t_parse_redir *current_redir, t_cmd *current_cmd)
{
	int	i;

	i = 0;
	while (current_redir->line[i] != NULL)
	{
		if (get_type(current_redir->line[i]) != WORD)
		{
			add_redir(current_cmd, current_redir->line[i + 1],
				get_type(current_redir->line[i]));
			i += 2;
		}
		else
		{
			current_cmd->args = ft_split(current_redir->line[i], ' ');
			i++;
		}
	}
}

void	fill_t_cmd(t_parse_redir *redir, t_cmd *cmd)
{
	t_parse_redir	*current_redir;
	t_cmd			*current_cmd;

	current_redir = redir;
	current_cmd = cmd;
	while (current_redir != NULL)
	{
		fill_line(current_redir, current_cmd);
		if (current_redir->next != NULL)
		{
			current_cmd->next = init_cmd();
			current_cmd->next->prev = current_cmd;
			current_cmd = current_cmd->next;
		}
		else
			current_cmd->next = NULL;
		current_redir = current_redir->next;
	}
}
