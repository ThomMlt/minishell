/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:25:30 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/16 14:53:37 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static char	*get_value_env(char *arg, t_env **env, int *index)
{
	char	*string;
	int		start;
	int		length;
	t_env	*current;

	*index += 1;
	start = *index;
	current = *env;
	while (ft_isalnum(arg[*index]) != 0 || arg[*index] == '_')
		*index += 1;
	string = ft_substr(arg, start, (*index - start));
	length = ft_strlen(string);
	while (current && ft_strncmp(string, current->key, length) != 0)
		current = current->next;
	free(string);
	if (current && current->value)
	{
		start = 0;
		length = ft_strlen(current->value);
		string = ft_substr(current->value, start, length);
	}
	else
		string = ft_strdup("");
	return (string);
}

void	expand_arg(char **arg, t_env **env, int last_status, int *index)
{
	char	*before_dollar;
	char	*str_to_expand;
	char	*end_str;
	char	*first_join;

	before_dollar = NULL;
	str_to_expand = NULL;
	end_str = NULL;
	before_dollar = ft_substr((*arg), 0, *index);
	if ((*arg)[*index + 1] == '?')
	{
		str_to_expand = ft_itoa(last_status);
		*index += 2;
	}
	else if (sep_var_name((*arg)[*index + 1]) == 0)
		str_to_expand = get_value_env((*arg), env, index);
	end_str = ft_substr((*arg), *index, (ft_strlen((*arg)) - *index));
	first_join = ft_strjoin(before_dollar, str_to_expand);
	free((*arg));
	(*arg) = ft_strjoin(first_join, end_str);
	free(before_dollar);
	free(str_to_expand);
	free(end_str);
	free(first_join);
	*index = -1;
}

void	handling_dollars(t_cmd *cmd, t_env **env, int last_status)
{
	t_cmd		*current;
	int			quote;
	int			i;
	int			j;

	current = cmd;
	while (current != NULL && current->args != NULL)
	{
		i = 0;
		while (current->args[i] != NULL)
		{
			j = 0;
			quote = NO_QUOTE;
			while (current->args[i][j] != '\0')
			{
				check_expand_quote(&quote, current->args[i][j]);
				if (current->args[i][j] == '$' && quote != S_QUOTE
					&& (sep_var_name(current->args[i][j + 1]) == 0))
					expand_arg(&current->args[i], env, last_status, &j);
				j++;
			}
			i++;
		}
		current = current->next;
	}
}
