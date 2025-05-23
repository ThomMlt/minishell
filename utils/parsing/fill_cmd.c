/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:17:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/17 12:04:05 by tmillot          ###   ########.fr       */
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

	return (cmd);
}

// void	fill_t_cmd(t_parse_redir *redir, t_cmd *cmd)
// {
// 	t_parse_redir	*current;
// 	t_cmd			*current_cmd;

// 	current = redir;
// 	current_cmd = cmd;
// 	//TODO: fill cmd
// }