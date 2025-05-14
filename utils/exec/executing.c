/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:16:30 by thomas            #+#    #+#             */
/*   Updated: 2025/05/12 14:07:52 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "cd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "env") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "exit") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "export") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "pwd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "unset") == 0)
		return (SUCCESS);
	else
		return (FAIL);
}

static void	find_built_in(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		if (is_built_in(current->args[0]) == SUCCESS)
			current->builtin = true;
		else
			current->builtin = false;
		current = current->next;
	}
}

int	wait_children(int status)
{
	int		cur_status;
	int		final_status;
	pid_t	prev_pid;
	pid_t	cur_pid;

	final_status = status;
	prev_pid = waitpid(-1, &cur_status, 0);
	while (prev_pid > 0)
	{
		cur_pid = waitpid(-1, &cur_status, 0);
		if (prev_pid < cur_pid)
			final_status = cur_status;
		prev_pid = cur_pid;
	}
	if (final_status == 131)
		ft_putstr_fd("quit (core dumped)\n", 2);
	return (final_status % 255);
}

int	ft_exec(t_cmd *cmd, t_env *env, int last_status)
{
	int		pipe_fd[2];
	int		prev_fd;

	find_built_in(cmd);
	expand_and_trim_cmd(cmd, env, last_status);
	if (cmd->next == NULL && is_special_built_in(cmd->args[0]) == SUCCESS)
		return (executing_special_built_in(cmd, env));
	last_status = EXIT_SUCCESS;
	prev_fd = STDIN_FILENO;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe error"), EXIT_FAILURE);
		last_status = ft_process(cmd, env, pipe_fd, prev_fd);
		if (prev_fd != 0)
			close(prev_fd);
		if (cmd->next != NULL)
			prev_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		close(pipe_fd[0]);
		cmd = cmd->next;
	}
	return (wait_children(last_status));
}
