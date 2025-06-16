/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollars_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:33:21 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:58:04 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	check_expand_quote(int *quote, char c)
{
	if (c == '\'' && *quote != D_QUOTE)
		return (*quote = S_QUOTE, 1);
	else if (c == '\"' && *quote != S_QUOTE)
		return (*quote = D_QUOTE, 1);
	return (0);
}

int	sep_var_name(char c)
{
	if (c == ' ' || c == '.' || c == '+' || c == '-' || c == '^' || c == ','
		|| c == '*' || c == '/' || c == '%' || c == '=' || c == '\"'
		|| c == '$' || c == '\0')
		return (1);
	return (0);
}

void	add_split_expand(t_cmd *current_cmd, char **split)
{
	int		i;
	int		index;
	char	**new;

	new = malloc(sizeof(char *)
			* (ft_split_len(split) + ft_split_len(current_cmd->args) + 1));
	i = 0;
	index = 0;
	while (split[i] != NULL)
	{
		new[index] = ft_strdup(split[i]);
		index++;
		i++;
	}
	i = 1;
	while (current_cmd->args[i] != NULL)
	{
		new[index] = ft_strdup(current_cmd->args[i]);
		index++;
		i++;
	}
	new[index] = NULL;
	clean_split(current_cmd->args);
	current_cmd->args = ft_strdup_split(new);
	clean_split(new);
}

void	split_first_args(t_cmd *cmd)
{
	t_cmd	*current;
	char	**split;

	current = cmd;
	split = NULL;
	while (current != NULL)
	{
		if (current->args != NULL)
		{
			split = ft_split(current->args[0], ' ');
			add_split_expand(current, split);
			clean_split(split);
			if (current->args[0] == NULL)
			{
				clean_split(current->args);
				current->args = NULL;
			}
		}
		current = current->next;
	}
}
