/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:55:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/05 10:42:46 by tmillot          ###   ########.fr       */
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

int	parse(char *line, t_cmd *cmd)
{
	char			**pipe;
	t_parse_redir	*redir;

	if (line == NULL)
		return (1);
	if (line[0] == '\0')
		return (1);
	if (check_if_valid_pipe(line, '|') == 1)
		return (ft_putstr_fd(ERR_PIPE, 2), 1);
	if (check_if_valid_redir(line) == 1)
		return (ft_putstr_fd(ERR_REDIR, 2), 1);
	if (check_quotes(line) == -1)
		return (ft_putstr_fd(ERR_QUOTE, 2), 1);
	pipe = ft_divide_char(line, '|');
	redir = init_redir();
	parse_redir(redir, pipe);
	if (fill_t_cmd(redir, cmd) == 1)
	{
		clean_pipe(pipe);
		clean_redir(redir);
		return (ft_putstr_fd(ERR_NO_FILE, 2), 1);
	}
	clean_pipe(pipe);
	clean_redir(redir);
	return (0);
}
