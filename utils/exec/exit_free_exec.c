/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:00:39 by tmillot           #+#    #+#             */
/*   Updated: 2025/04/30 15:29:56 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	free_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_t_redir(t_redir *list)
{
	t_redir		*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	free_t_cmd(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		free_tab_char(cmd->args);
		if (cmd->infile != NULL)
			free_t_redir(cmd->infile);
		if (cmd->outfile != NULL)
			free_t_redir(cmd->outfile);
		cmd = cmd->next;
		free(cmd);
	}
}

int	ft_exit_exec(int exit_code, t_cmd *cmd, char **envp, char *path_cmd)
{
	free(path_cmd);
	free_t_cmd(cmd);
	free_tab_char(envp);
	exit(exit_code);
}
