/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:00:39 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/21 16:23:23 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	free_tab_char(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		if (tab[i])
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
		if (list->type == HEREDOC)
		{
			if (unlink(list->file) == -1)
				perror("unlink error");
		}
		else
		{
			if (list->file != NULL)
				free(list->file);
		}
		temp = list;
		list = list->next;
		free(temp);
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

void	free_path(char *path_cmd)
{
	if (path_cmd != NULL)
		free(path_cmd);
}

void	ft_exit_exec(t_cmd *cmd)
{
	if (cmd != NULL)
		free_t_cmd(cmd);
}

void	ft_exit_child_process(int code_status, char *path_cmd, char **envp)
{
	if (path_cmd != NULL)
		free_path(path_cmd);
	if (envp != NULL)
		free_tab_char(envp);
	exit(code_status);
}
