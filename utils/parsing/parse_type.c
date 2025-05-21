/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:42:43 by lidbaha           #+#    #+#             */
/*   Updated: 2025/03/26 18:27:48 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	parse_pipe(t_parse *cmd, char *line)
{
	char			**tmp;
	t_parse_pipe	*pipe;

	pipe = malloc(sizeof(t_parse_pipe));
	tmp = ft_minishell_split_char(line, '|');
	pipe->line = ft_strdup_split(tmp);
	cmd->pipe = pipe;
	clean_split(tmp);
}

void	parse_redir_input(t_parse *cmd, char *line)
{
	char				**tmp;
	t_parse_redir_input	*redir_input;

	redir_input = malloc(sizeof(t_parse_redir_input));
	tmp = ft_minishell_split_char(line, '<');
	redir_input->line = ft_strdup_split(tmp);
	cmd->redir_input = redir_input;
	clean_split(tmp);
}

void	parse_redir_output(t_parse *cmd, char *line)
{
	char					**tmp;
	t_parse_redir_output	*redir_output;

	redir_output = malloc(sizeof(t_parse_redir_output));
	tmp = ft_minishell_split_char(line, '>');
	redir_output->line = ft_strdup_split(tmp);
	cmd->redir_output = redir_output;
	clean_split(tmp);
}

void	parse_redir_append(t_parse *cmd, char *line)
{
	char					**tmp;
	t_parse_redir_append	*redir_append;

	redir_append = malloc(sizeof(t_parse_redir_append));
	tmp = ft_minishell_split_char(line, '>');
	redir_append->line = ft_strdup_split(tmp);
	cmd->redir_append = redir_append;
	clean_split(tmp);
}

void	parse_redir_heredoc(t_parse *cmd, char *line)
{
	char					**tmp;
	t_parse_redir_heredoc	*redir_heredoc;

	redir_heredoc = malloc(sizeof(t_parse_redir_heredoc));
	tmp = ft_minishell_split_char(line, '<');
	redir_heredoc->line = ft_strdup_split(tmp);
	cmd->redir_heredoc = redir_heredoc;
	clean_split(tmp);
}
