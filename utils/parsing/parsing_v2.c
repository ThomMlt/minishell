/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:55:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/23 13:07:19 by tmillot          ###   ########.fr       */
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

char	*skip_quotes(char *line, char quote)
{
	line++;
	while (*line != quote)
		line++;
	line++;
	return (line);
}

int	check_if_valid(char *line, char sep)
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

t_parse_redir	*init_redir(void)
{
	t_parse_redir	*redir;

	redir = malloc(sizeof(t_parse_redir));
	if (!redir)
		return (NULL);
	redir->line = NULL;
	redir->next = NULL;
	return (redir);
}

int	parse_v2(char *line, t_env *env, int last_status)
{
	int				i;
	char			**pipe;
	t_parse_redir	*redir;
	t_cmd			*cmd;

	i = 0;
	if (line[0] == '\0')
		return (last_status);
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (check_quote_closed(line, i + 1, line[i]) != -1)
				i = check_quote_closed(line, i + 1, line[i]) + 1;
			else
				exit(1); //TODO: return error (unclosed quote)
		}
		i++;
	}
	if (check_if_valid(line, '|') == 1)
		return (last_status); //TODO: return error (missing pipe argument)
	pipe = ft_divide_char(line, '|');
	redir = init_redir();
	parse_redir(redir, pipe);
	cmd = init_cmd();
	fill_t_cmd(redir, cmd);
	clean_pipe(pipe);
	clean_redir(redir);
	// print_cmd_debug(cmd);
	last_status = ft_exec(cmd, env, last_status);
	return (last_status);
}
