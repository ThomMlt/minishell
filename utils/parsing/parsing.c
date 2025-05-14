/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:10:52 by lidbaha           #+#    #+#             */
/*   Updated: 2025/03/25 16:12:22 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	parse_space(t_parse *cmd, char *line)
{
	char			**tmp;
	t_parse_space	*space;

	space = malloc(sizeof(t_parse_space));
	tmp = ft_split(line, ' ');
	space->line = ft_strdup_split(tmp);
	cmd->space = space;
	clean_split(tmp);
}

void	check_line(t_parse *cmd)
{
	if (cmd->space->line[0] == NULL)
		return ;
	if (ft_strcmp(cmd->space->line[0], "exit") == 0
		&& cmd->space->line[1] == NULL)
	{
		clean_cmd(cmd);
		clean_env();
		exit(0);
	}
}

t_quotes	*init_quotes(void)
{
	t_quotes	*tmp;

	tmp = malloc(sizeof(t_quotes));
	tmp->line = NULL;
	tmp->index = 0;
	tmp->next = NULL;
	return (tmp);
}

void	parse(char *line)
{
	t_parse			*cmd;
	t_quotes		*quotes;

	if (line[0] != '\0')
	{
		cmd = malloc(sizeof(t_parse));
		quotes = init_quotes();
		cmd->line = ft_strdup(line);
		line = remove_quotes(line, quotes);
		parse_space(cmd, line);
		parse_pipe(cmd, line);
		parse_redir_input(cmd, line);
		parse_redir_output(cmd, line);
		parse_redir_append(cmd, line);
		parse_redir_heredoc(cmd, line);
		//replace_quotes(cmd, quotes);
		check_line(cmd);
		clean_quotes(quotes);
		clean_cmd(cmd);
	}
	else
		free(line);
}
