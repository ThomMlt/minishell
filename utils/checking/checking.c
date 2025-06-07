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

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == line[i] && line[i + 2] == line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_valid_pipe(char *line, char sep)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	if (line[0] == sep && line[1] != sep)
		return (1);
	while (line[i] != '\0')
	{
		if (line[i] == sep && line[i + 1] != sep && line[i - 1] != sep)
		{
			if (valid == 1)
				return (1);
			valid = 1;
			if (line[i + 1] == '\0')
				return (1);
			i++;
		}
		if (valid == 1)
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
				&& line[i] != '\r' && line[i] != 32)
				valid = 0;
		i++;
	}
	return (valid);
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
				i = check_quote_closed(line, i + 1, line[i]) + 1;
			else
				return (-1);
		}
		if (line[i] != '\0')
			i++;
	}
	return (0);
}
