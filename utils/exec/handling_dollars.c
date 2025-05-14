/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:25:30 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/10 13:19:29 by tmillot          ###   ########.fr       */
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

static int	sep_var_name(char c)
{
	if (c == ' ' || c == '.' || c == '+' || c == '-' || c == '^' || c == ','
		|| c == '*' || c == '/' || c == '%' || c == '=' || c == '\"'
		|| c == '\0')
		return (0);
	return (1);
}

static char	*get_value_env(char *arg, t_env *env, int *index)
{
	char	*value;
	char	*name;
	int		start;
	t_env	*current;

	start = *index + 1;
	name = NULL;
	current = env;
	value = ft_strdup("");
	if (ft_isdigit(arg[start]) == 1)
		return ((*index) += 2, value);
	while (sep_var_name(arg[*index]) == 1 && arg[*index] != '\0')
		*index += 1;
	name = ft_substr(arg, start, (*index - start));
	while (current != NULL)
	{
		if (ft_strcmp(name, current->key) == 0)
		{
			free(value);
			value = ft_strdup(current->value);
			break ;
		}
		current = current->next;
	}
	return (free(name), value);
}

void	expand_arg(char **arg, t_env *env, int last_status, int *index)
{
	char	*before_dollar;
	char	*str_to_expand;
	char	*end_str;
	char	*first_join;

	before_dollar = NULL;
	str_to_expand = ft_strdup("");
	end_str = NULL;
	before_dollar = ft_substr((*arg), 0, *index);
	if ((*arg)[*index + 1] == '?')
	{
		str_to_expand = ft_itoa(last_status);
		*index += 2;
	}
	else if (sep_var_name((*arg)[*index + 1]) == 1)
		str_to_expand = get_value_env((*arg), env, index);
	end_str = ft_substr((*arg), *index, (ft_strlen((*arg)) - *index));
	first_join = ft_strjoin(before_dollar, str_to_expand);
	free((*arg));
	(*arg) = ft_strjoin(first_join, end_str);
	free(before_dollar);
	free(str_to_expand);
	free(end_str);
	free(first_join);
}

void	handling_dollars(t_cmd *cmd, t_env *env, int last_status)
{
	t_cmd		*current;
	int			quote;
	int			i;
	int			j;

	current = cmd;
	while (current != NULL)
	{
		i = 0;
		while (current->args[i] != NULL)
		{
			j = 0;
			quote = NO_QUOTE;
			while (current->args[i][j] != '\0')
			{
				check_expand_quote(&quote, current->args[i][j]);
				if (current->args[i][j] == '$' && quote != S_QUOTE)
					expand_arg(&current->args[i], env, last_status, &j);
				j++;
			}
			i++;
		}
		current = current->next;
	}
}
