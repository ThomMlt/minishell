/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_trim_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:15:48 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:58:01 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	expand_trim_redir(t_redir *redirection, t_env **env, int last_status)
{
	t_redir		*current;
	int			quote;
	int			i;

	current = redirection;
	quote = NO_QUOTE;
	while (current != NULL)
	{
		i = 0;
		while (current->file[i] != '\0')
		{
			check_expand_quote(&quote, current->file[i]);
			if (current->file[i] == '$' && quote != S_QUOTE)
				expand_arg(&current->file, env, last_status, &i);
			i++;
		}
		find_and_trim_quote(&current->file);
		current = current->next;
	}
}

int	if_dollars(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;
	int		j;

	current = cmd;
	if (cmd->args == NULL)
		return (1);
	while (current != NULL)
	{
		i = 0;
		while (current->args[i] != NULL)
		{
			j = 0;
			while (current->args[i][j] != '\0')
			{
				if (current->args[i][j] == '$')
					return (0);
				j++;
			}
			i++;
		}
		current = current->next;
	}
	return (1);
}

int	expand_and_trim_cmd(t_cmd *cmd, t_env **env, int last_status)
{
	t_cmd	*current;
	int		dollars_before;
	int		dollars_after;

	current = cmd;
	dollars_before = if_dollars(cmd);
	handling_dollars(cmd, env, last_status);
	trim_quotes(cmd);
	dollars_after = if_dollars(cmd);
	if (dollars_before == 0 && dollars_after == 1)
		split_first_args(cmd);
	while (current != NULL)
	{
		if (current->infile != NULL)
			expand_trim_redir(current->infile, env, last_status);
		if (current->outfile != NULL)
			expand_trim_redir(current->outfile, env, last_status);
		current = current->next;
	}
	return (0);
}
