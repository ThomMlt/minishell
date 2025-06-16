/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:00:39 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:58:00 by tmillot          ###   ########.fr       */
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
			if (access(list->file, F_OK) == 0)
			{
				if (unlink(list->file) == -1)
					perror("unlink error");
			}
			free(list->file);
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

void	free_path(char *path_cmd)
{
	if (path_cmd != NULL)
		free(path_cmd);
}

int	wait_and_free(int status, t_cmd *cmd)
{
	int	last_status;

	last_status = 0;
	if (cmd == NULL)
		return (status);
	if (cmd != NULL)
	{
		last_status = wait_children(status, cmd);
	}
	return (last_status);
}

void	ft_exit_child(int code_status, char *path_cmd, char **envp)
{
	if (path_cmd != NULL)
		free_path(path_cmd);
	if (envp != NULL)
		free_tab_char(envp);
	exit(code_status);
}
