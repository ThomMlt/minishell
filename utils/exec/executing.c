/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:16:30 by thomas            #+#    #+#             */
/*   Updated: 2025/06/10 21:08:52 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	is_built_in(char *str)
{
	if (str == NULL)
		return (FAIL);
	else if (ft_strcmp(str, "echo") == 0)
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
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		if (current->args != NULL)
		{
			if (is_built_in(current->args[0]) == SUCCESS)
				current->builtin = true;
		}
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
	int		signal_num;

	current = cmd;
	last_status = status;
	cur_status = 0;
	while (current != NULL)
	{
		waitpid(current->pid, &cur_status, 0);
		if (WIFEXITED(cur_status))
			last_status = WEXITSTATUS(cur_status);
		else if (WIFSIGNALED(cur_status))
		{
			signal_num = WTERMSIG(cur_status);
			if (signal_num == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			last_status = 128 + signal_num;
		}
		current = current->next;
	}
	return (free_t_cmd(cmd), last_status % 256);
}

int	is_special_build_parent(char **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return (1);
	if (ft_strncmp(cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd[0], "export", 7) == 0
		|| ft_strncmp(cmd[0], "unset", 6) == 0
		|| ft_strncmp(cmd[0], "exit", 5) == 0)
		return (0);
	return (1);
}

int	ft_exec_special_builtin(t_env **env, t_cmd *cmd)
{
	int	status;

	status = exec_builtin(cmd, env);
	free_t_cmd(cmd);
	return (status);
}

int	set_and_expand(t_cmd *cmd, t_env **env, int last_status)
{
	int	value;

	value = expand_and_trim_cmd(cmd, env, last_status);
	find_built_in(cmd);
	return (value);
}

int	ft_exec(t_cmd *cmd, t_env **env, int last_status)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_fd;

	if (set_and_expand(cmd, env, last_status) == 1)
		return (free_t_cmd(cmd), last_status);
	prev_fd = STDIN_FILENO;
	current = cmd;
	setup_signal(1);
	if (current->next == NULL && is_special_build_parent(current->args) == 0)
		return (ft_exec_special_builtin(env, current));
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
