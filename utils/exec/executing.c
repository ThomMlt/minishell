/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:16:30 by thomas            #+#    #+#             */
/*   Updated: 2025/05/29 12:05:54 by tmillot          ###   ########.fr       */
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

int	wait_children(int status, t_cmd *cmd)
{
	t_cmd	*current;
	int		last_status;
	int		cur_status;

	current = cmd;
	last_status = status;
	cur_status = 0;
	while (current != NULL)
	{
		waitpid(current->pid, &cur_status, 0);
		if (WIFEXITED(cur_status))
			last_status = WEXITSTATUS(cur_status);
		else if (WIFSIGNALED(cur_status))
			last_status = 128 + WTERMSIG(cur_status);
		current = current->next;
	}
	free_t_cmd_nowhere(cmd);
	return (last_status % 255);
}

int	is_special_build_in_parent(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd[0], "export", 7) == 0
		|| ft_strncmp(cmd[0], "unset", 6) == 0
		|| ft_strncmp(cmd[0], "exit", 5) == 0)
		return (0);
	return (1);
}

int	ft_exec(t_cmd *cmd, t_env **env, int last_status)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_fd;

	find_built_in(cmd);
	expand_and_trim_cmd(cmd, env, last_status);
	prev_fd = STDIN_FILENO;
	current = cmd;
	if (current->next == NULL && is_special_build_in_parent(current->args) == 0)
		return (exec_builtin(current, env));
	while (current != NULL)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe error"), EXIT_FAILURE);
		last_status = ft_process(current, env, pipe_fd, prev_fd);
		close(pipe_fd[1]);
		if (prev_fd != 0)
			close(prev_fd);
		if (current->next != NULL)
			prev_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		current = current->next;
	}
	return (wait_and_free(last_status, cmd));
}
