/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 10:48:05 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/06 15:08:34 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

t_redir	*add_redir_node(char *file, t_token_type type)
{
	t_redir	*node;

	node = init_cmd_redir();
	if (type == HEREDOC)
	{
		node->file = get_here_doc(file);
		if (node->file == NULL)
			return (clean_t_redir(node), NULL);
	}
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

int	add_redir_infile(t_cmd *current_cmd, char *file, t_token_type type)
{
	t_redir	*temp;

	if (current_cmd->infile == NULL)
	{
		current_cmd->infile = add_redir_node(file, type);
		if (current_cmd->infile == NULL)
			return (1);
	}
	else
	{
		temp = current_cmd->infile;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = add_redir_node(file, type);
		if (temp->next == NULL)
			return (1);
	}
	return (0);
}

int	add_redir(t_cmd *current_cmd, char *file, t_token_type type)
{
	char	**split;

	if (file == NULL)
		return (1);
	split = ft_divide_char_all(file, ' ');
	if (type == REDIRECT_APPEND || type == REDIRECT_OUT)
	{
		add_redir_outfile(current_cmd, split[0], type);
	}
	else if (type == REDIRECT_IN || type == HEREDOC)
	{
		if (add_redir_infile(current_cmd, split[0], type) == 1)
			return (clean_split(split), 2);
	}
	if (split[1] != NULL)
	{
		if (current_cmd->args == NULL)
			current_cmd->args = ft_strndup_split(split, 1);
		else
			add_split(current_cmd, split);
	}
	clean_split(split);
	return (0);
}
