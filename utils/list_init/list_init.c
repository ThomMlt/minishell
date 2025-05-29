/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 06:57:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/23 18:08:20 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->prev = NULL;

	return (cmd);
}

t_redir	*init_cmd_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->next = NULL;
	return (redir);
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