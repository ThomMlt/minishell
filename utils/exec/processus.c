/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:58:31 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/23 13:13:29 by tmillot          ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(env, cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(&env, cmd));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(&env, cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, &env), ft_printf("Builtin premier node env : %s\n", env->key), 0);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, env, 0));
	return (1);
}

int	child_process(t_env *env, t_cmd *cmd, char **envp, char *path_cmd)
{
	struct stat	data;

	if (*cmd->args[0] == '.' || *cmd->args[0] == '/')
		ft_exit_child(run_executable(cmd, envp), path_cmd, envp);
	else if (cmd->builtin == true)
		ft_exit_child(exec_builtin(cmd, env), path_cmd, envp);
	else if (path_cmd == NULL)
		ft_exit_child(127, path_cmd, envp);
	else if (stat(path_cmd, &data) != 0)
		return (perror("stat"), CODE_FAIL);
	else if (S_ISREG(data.st_mode) == 0)
		return (is_a_directory(cmd->args[0]), 126);
	else if (execve(path_cmd, cmd->args, envp) == -1)
		perror("execve");
	return (ft_exit_child(CODE_FAIL, path_cmd, envp), CODE_FAIL);
}

int	ft_process(t_cmd *cmd, t_env *env, int *pipe_fd, int prev_fd)
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
		envp = env_tab_char(env);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (perror("fork"), CODE_FAIL);
	if (cmd->pid != 0)
		return (CODE_SUCCESS);
	redir = redirect_management(cmd, pipe_fd, prev_fd);
	if (redir == CODE_SUCCESS && cmd->args[0])
		ft_exit_child(child_process(env, cmd, envp, path_cmd), path_cmd, envp);
	else
		ft_exit_child(redir, path_cmd, envp);
	return (CODE_SUCCESS);
}
