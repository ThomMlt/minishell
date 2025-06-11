/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:48:05 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/10 18:09:00 by tmillot          ###   ########.fr       */
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

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	remove_space(t_cmd *current_cmd)
{
	char	**new;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (current_cmd->args[i] != NULL)
	{
		if (current_cmd->args[i][0] != ' ' && !is_only_spaces(current_cmd->args[i]))
			size++;
		i++;
	}
	new = malloc(sizeof(char *) * (size + 1));
	i = 0;
	size = 0;
	while (current_cmd->args[i] != NULL)
	{
		if (current_cmd->args[i][0] != ' ' && !is_only_spaces(current_cmd->args[i]))
		{
			new[size] = ft_strdup(current_cmd->args[i]);
			size++;
		}
		i++;
	}
	new[size] = NULL;
	clean_split(current_cmd->args);
	current_cmd->args = ft_strdup_split(new);
	clean_split(new);
}

int	fill_line(t_parse_redir *current_redir, t_cmd *current_cmd)
{
	int	i;

	i = 0;
	while (current_redir->line[i] != NULL)
	{
		if (get_type(current_redir->line[i]) != WORD)
		{
			if (add_redir(current_cmd, current_redir->line[i + 1],
					get_type(current_redir->line[i])) == 1)
				return (1);
			if (current_cmd->args != NULL)
				remove_space(current_cmd);
			i += 2;
		}
		else
		{
			if (current_redir->line[i][0] != '\0')
			{
 				current_cmd->args = ft_divide_char(current_redir->line[i], ' ');
				remove_space(current_cmd);
			}
			i++;
		}
	}
	return (0);
}

int	fill_t_cmd(t_parse_redir *redir, t_cmd *cmd)
{
	t_parse_redir	*current_redir;
	t_cmd			*current_cmd;

	current_redir = redir;
	current_cmd = cmd;
	while (current_redir != NULL)
	{
		if (current_redir->line[0][0] != '|')
		{
			if (fill_line(current_redir, current_cmd) == 1)
				return (1);
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
		else
			if (current_redir->next != NULL)
				current_redir = current_redir->next;
	}
	return (0);
}
