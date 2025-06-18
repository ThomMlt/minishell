/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:36:01 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/16 15:36:32 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	exec_builtin_child(t_cmd *cmd, t_env **env, char **envp)
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
		return (clean_split(envp), ft_exit(cmd, env, 0));
	return (1);
}
