/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:48:05 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/02 11:17:04 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

t_redir	*add_redir_node(char *file, t_token_type type)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	node = init_cmd_redir();
	if (type == HEREDOC)
		node->file = get_here_doc(file);
	else
		node->file = ft_strdup(file);
	node->type = type;
	return (node);
}

void	add_redir_outfile(t_cmd *current_cmd, char *file, t_token_type type)
{
	t_redir	*temp;

	if (current_cmd->outfile == NULL)
		current_cmd->outfile = add_redir_node(file, type);
	else
	{
		temp = current_cmd->outfile;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = add_redir_node(file, type);
	}
}

void	add_redir_infile(t_cmd *current_cmd, char *file, t_token_type type)
{
	t_redir	*temp;

	if (current_cmd->infile == NULL)
		current_cmd->infile = add_redir_node(file, type);
	else
	{
		temp = current_cmd->infile;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = add_redir_node(file, type);
	}
}

void	add_redir(t_cmd *current_cmd, char *file, t_token_type type)
{
	char	**split;

	split = ft_split(file, ' ');
	if (type == REDIRECT_APPEND || type == REDIRECT_OUT)
	{
		add_redir_outfile(current_cmd, split[0], type);
	}
	else if (type == REDIRECT_IN)
	{
		add_redir_infile(current_cmd, split[0], type);
	}
	if (split[1] != NULL)
		add_split(current_cmd, split);
	clean_split(split);
}
