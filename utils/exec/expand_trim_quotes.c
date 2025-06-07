/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_trim_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:15:48 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/07 14:51:36 by tmillot          ###   ########.fr       */
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

void	expand_and_trim_cmd(t_cmd *cmd, t_env **env, int last_status)
{
	t_cmd	*current;

	current = cmd;
	handling_dollars(cmd, env, last_status);
	trim_quotes(cmd);
	while (current != NULL)
	{
		if (current->infile != NULL)
			expand_trim_redir(current->infile, env, last_status);
		if (current->outfile != NULL)
			expand_trim_redir(current->outfile, env, last_status);
		current = current->next;
	}
}
