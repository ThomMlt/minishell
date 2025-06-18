/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:04:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/16 20:04:57 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	valid_pipe(char *line, int *word, int *i, int *pipe)
{
	if (line[*i] == '\'' || line[*i] == '\"')
	{
		*i = check_quote_closed(line, *i + 1, line[*i]);
		*word = 1;
	}
	else
	{
		if (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '|'
			&& line[*i] != '>' && line[*i] != '<')
			*word = 1;
		else if (line[*i] == '|')
		{
			*pipe = 1;
			if (*word == 0)
				return (1);
			*word = 0;
		}
	}
	return (0);
}

int	valid_redir(char *line, t_check_redir *c_r)
{
	if (line[c_r->i] == '\'' || line[c_r->i] == '\"')
	{
		c_r->i = check_quote_closed(line, c_r->i + 1, line[c_r->i]);
		c_r->word = 1;
	}
	else
	{
		if (line[c_r->i] == '>' || line[c_r->i] == '<')
		{
			c_r->redir = 1;
			if (line[c_r->i + 1] == line[c_r->i]
				&& line[c_r->i + 2] == line[c_r->i])
				return (1);
			if (c_r->first_redir == 1)
				c_r->first_redir = 0;
			else if (c_r->word == 0 && line[c_r->i - 1] != line[c_r->i])
				return (1);
			c_r->word = 0;
		}
		else if (line[c_r->i] != ' ' && line[c_r->i] != '\t'
			&& line[c_r->i] != '|')
			c_r->word = 1;
	}
	return (0);
}
