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

char	*tab_to_space(char *line)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (ft_strlen(line) + 1));
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
			new[i] = ' ';
		else
			new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	checks(char *input)
{
	if (check_quotes(input) == -1)
		return (ft_putstr_fd(ERR_QUOTE, 2), 2);
	if (check_if_valid_pipe(input) == 1)
		return (ft_putstr_fd(ERR_PIPE, 2), 2);
	if (check_if_valid_redir(input) == 1)
		return (ft_putstr_fd(ERR_REDIR, 2), 2);
	return (0);
}

int	parse(char *input, t_cmd *cmd)
{
	char			**pipe;
	char			*line;
	int				status;
	t_parse_redir	*redir;

	if (input == NULL)
		return (1);
	if (input[0] == '\0' || is_only_spaces(input) == 1)
		return (1);
	if (checks(input) == 2)
		return (2);
	line = tab_to_space(input);
	pipe = ft_divide_char(line, '|');
	redir = init_redir();
	parse_redir(redir, pipe);
	status = fill_t_cmd(redir, cmd);
	if (status != 0)
	{
		(clean_pipe(pipe), clean_redir(redir));
		if (status == 1)
			return (ft_putstr_fd(ERR_NO_FILE, 2), free(line), 1);
		return (free(line), 1);
	}
	return (clean_pipe(pipe), clean_redir(redir), free(line), 0);
}
