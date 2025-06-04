/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:58:31 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/03 17:30:06 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static int	run_executable(t_cmd *cmd, char **envp)
{
	struct stat	data;

	if (access(cmd->args[0], F_OK) == -1)
		return (command_not_found(cmd->args[0]), 127);
	if (access(cmd->args[0], X_OK) == -1)
		return (permission_denied(cmd->args[0]), 126);
	if (stat(cmd->args[0], &data) != 0)
		return (perror("stat"), CODE_FAIL);
	if (S_ISREG(data.st_mode) == 0)
		return (is_a_directory(cmd->args[0]), 126);
	if (execve(*cmd->args, cmd->args, envp) == -1)
		perror("execve");
	return (CODE_FAIL);
}

int	exec_builtin(t_cmd *cmd, t_env **env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(env, cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(env, cmd));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(env, cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, env, 0));
	return (1);
}

void	child_process(t_env **env, t_cmd *cmd, char **envp, char *path)
{
	struct stat		data;
	int				value_exit;

	value_exit = 0;
	setup_signal(0);
	if (*cmd->args[0] == '.' || *cmd->args[0] == '/')
		value_exit = run_executable(cmd, envp);
	else if (cmd->builtin == true)
		value_exit = exec_builtin(cmd, env);
	else if (path == NULL)
		value_exit = 127;
	else if (stat(path, &data) != 0)
		perror("stat");
	else if (S_ISREG(data.st_mode) == 0)
	{
		is_a_directory(cmd->args[0]);
		value_exit = 126;
	}
	else if (execve(path, cmd->args, envp) == -1)
	{
		perror("execve");
		value_exit = CODE_FAIL;
	}
	(free_env(env), free_t_cmd_nowhere(cmd));
	ft_exit_child(value_exit, path, envp);
}

int	ft_process(t_cmd *cmd, t_env **env, int *pipe_fd, int prev_fd)
{
	char	*path_cmd;
	int		redir;
	char	**envp;

	if (env == NULL && cmd->args[0] != NULL && is_built_in(*cmd->args) == FAIL)
		return (no_such_file_or_directory(cmd->args[0]), 127);
	path_cmd = NULL;
	envp = NULL;
	if (cmd->args[0] != NULL && *cmd->args[0] != '.'
		&& *cmd->args[0] != '/' && is_built_in(*cmd->args) == FAIL)
	{
		path_cmd = find_cmd_path(env, cmd);
		envp = env_tab_char(env, path_cmd);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), CODE_FAIL);
	if (cmd->pid != 0)
		return (safe_free_exec(cmd, envp, path_cmd), CODE_SUCCESS);
	redir = redirect_management(cmd, pipe_fd, prev_fd);
	if (redir == CODE_SUCCESS && cmd->args[0])
		child_process(env, cmd, envp, path_cmd);
	(free_env(env), free_t_cmd_nowhere(cmd));
	ft_exit_child(redir, path_cmd, envp);
	return (CODE_SUCCESS);
}
