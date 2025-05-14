/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:00:58 by tmillot           #+#    #+#             */
/*   Updated: 2025/04/30 11:23:59 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static int	management_infile(t_cmd *cmd, int prev_fd)
{
	int	in_fd;

	if (cmd->infile == NULL && prev_fd == 0)
		return (CODE_SUCCESS);
	if (cmd->infile == NULL && prev_fd != 0)
		return (dup2(prev_fd, 0), close(prev_fd), CODE_SUCCESS);
	if (prev_fd != 0)
		close(prev_fd);
	in_fd = last_infile(cmd);
	if (in_fd == -1)
		return (CODE_FAIL);
	return (dup2(in_fd, 0), close(in_fd), CODE_SUCCESS);
}

static int	management_outfile(t_cmd *cmd, int *pipe_fd)
{
	int	out_fd;

	if (cmd->outfile == NULL && cmd->next == NULL)
		return (CODE_SUCCESS);
	if (cmd->outfile == NULL)
		return (dup2(pipe_fd[1], 1), CODE_SUCCESS);
	out_fd = last_infile(cmd);
	if (out_fd == -1)
		return (dup2(pipe_fd[1], 1), CODE_FAIL);
	return (dup2(out_fd, 1), close(out_fd), CODE_FAIL);
}

int	redirect_management(t_cmd *cmd, int *pipe_fd, int prev_fd)
{
	if (management_infile(cmd, prev_fd) == CODE_FAIL)
		return (close(pipe_fd[0]), close(pipe_fd[1]), CODE_FAIL);
	if (management_outfile(cmd, pipe_fd) == CODE_FAIL)
		return (close(pipe_fd[0]), close(pipe_fd[1]), CODE_FAIL);
	return (close(pipe_fd[0]), close(pipe_fd[1]), CODE_SUCCESS);
}
