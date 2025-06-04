/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:55:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/27 11:47:57 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

char	*skip_quotes(char *line, char quote)
{
	line++;
	while (*line != quote)
		line++;
	line++;
	return (line);
}

void	parse(char *line, t_cmd *cmd)
{
	char			**pipe;
	t_parse_redir	*redir;

	if (line == NULL)
		return ; // do nothing if line is NULL
	if (line[0] == '\0')
		return ; // do nothing if line is empty
	if (check_if_valid_pipe(line, '|') == 1)
		return ; // return pipe error
	if (check_if_valid_redir(line) == 1)
		return ; // return redirection error
	if (check_quotes(line) == -1)
		return ; // return quote error
	pipe = ft_divide_char(line, '|');
	redir = init_redir();
	parse_redir(redir, pipe);
	fill_t_cmd(redir, cmd);
	clean_pipe(pipe);
	clean_redir(redir);
}
