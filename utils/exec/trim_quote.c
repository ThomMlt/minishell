/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 07:06:39 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/12 17:53:51 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	check_status_quote(int *quote, char c)
{
	if (c == '\'' && *quote == NO_QUOTE)
		return (*quote = S_QUOTE, 1);
	else if (c == '\'' && *quote == S_QUOTE)
		return (*quote = NO_QUOTE, 1);
	else if (c == '\"' && *quote == NO_QUOTE)
		return (*quote = D_QUOTE, 1);
	else if (c == '\"' && *quote == D_QUOTE)
		return (*quote = NO_QUOTE, 1);
	return (0);
}

void	change_str(char *arg, int len)
{
	int	i;

	i = 0;
	while (arg[i + len] != '\0')
	{
		arg[i] = arg[i + len];
		i++;
	}
	arg[i] = '\0';
}

void	find_and_trim_quote(char **arg)
{
	int	index;
	int	quote;

	index = 0;
	quote = NO_QUOTE;
	while ((*arg)[index] != '\0')
	{
		check_status_quote(&quote, (*arg)[index]);
		if (((*arg)[index] == '\"' && quote != S_QUOTE))
			change_str((*arg) + index--, 1);
		else if ((*arg)[index] == '\'' && quote != D_QUOTE)
			change_str((*arg) + index--, 1);
		index++;
	}
}

void	trim_quotes(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	while (current != NULL)
	{
		i = 0;
		while (current->args[i] != NULL)
		{
			find_and_trim_quote(&current->args[i]);
			i++;
		}
		current = current->next;
	}
}
