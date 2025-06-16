/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:34:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/02 13:34:57 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	check_quote_closed(char *line, int index, char quote)
{
	while (line[index] != '\0')
	{
		if (line[index] == quote)
			break ;
		index++;
	}
	if (line[index] == quote)
		return (index);
	return (-1);
}

int	check_if_valid_redir(char *line)
{
	int	i;
	int	word;
	int	redir;
	int	first_redir;

	i = 0;
	word = 0;
	redir = 0;
	first_redir = 1;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = check_quote_closed(line, i + 1, line[i]);
			word = 1;
		}
		else
		{
			if (line[i] == '>' || line[i] == '<')
			{
				redir = 1;
				if (line[i + 1] == line[i] && line[i + 2] == line[i])
					return (1);
				if (first_redir == 1)
					first_redir = 0;
				else if (word == 0 && line[i - 1] != line[i])
					return (1);
				word = 0;
			}
			else if (line[i] != ' ' && line[i] != '\t' && line[i] != '|')
				word = 1;
		}
		i++;
	}
	if (redir == 1 && word == 0)
		return (1);
	return (0);
}

int	check_if_valid_pipe(char *line)
{
	int	i;
	int	word;
	int	pipe;

	i = 0;
	word = 0;
	pipe = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i = check_quote_closed(line, i + 1, line[i]);
			word = 1;
		}
		else
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '|'
				&& line[i] != '>' && line[i] != '<')
				word = 1;
			else if (line[i] == '|')
			{
				pipe = 1;
				if (word == 0)
					return (1);
				word = 0;
			}
		}
		i++;
	}
	if (pipe == 1 && word == 0)
		return (1);
	return (0);
}

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (check_quote_closed(line, i + 1, line[i]) != -1)
				i = check_quote_closed(line, i + 1, line[i]);
			else
				return (-1);
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
}
