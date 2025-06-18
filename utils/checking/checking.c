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
	t_check_redir	*check_redir;

	check_redir = malloc(sizeof(t_check_redir));
	check_redir->i = 0;
	check_redir->word = 0;
	check_redir->redir = 0;
	check_redir->first_redir = 1;
	while (line[check_redir->i] != '\0')
	{
		if (valid_redir(line, check_redir) == 1)
			return (free(check_redir), 1);
		check_redir->i++;
	}
	if (check_redir->redir == 1 && check_redir->word == 0)
		return (free(check_redir), 1);
	return (free(check_redir), 0);
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
		if (valid_pipe(line, &word, &i, &pipe) == 1)
			return (1);
		i++;
	}
	return (pipe == 1 && word == 0);
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
