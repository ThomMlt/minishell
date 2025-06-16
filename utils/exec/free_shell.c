/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 04:01:30 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:58:03 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (cmd != NULL)
	{
		tmp = cmd;
		free_tab_char(cmd->args);
		if (cmd->infile != NULL)
			free_t_redir(cmd->infile);
		if (cmd->outfile != NULL)
			free_t_redir(cmd->outfile);
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_t_cmd_nowhere(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	free_t_cmd(tmp);
}

void	safe_free_exec(t_cmd *cmd, char **envp, char *path)
{
	(void)cmd;
	free_tab_char(envp);
	free_path(path);
}
