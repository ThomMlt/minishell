/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:26:09 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:57:59 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

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
