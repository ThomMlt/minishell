/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speciale_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:06:03 by tmillot           #+#    #+#             */
/*   Updated: 2025/04/30 11:24:03 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	is_special_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(cmd, "export") == 0)
		return (SUCCESS);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (SUCCESS);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (SUCCESS);
	else
		return (FAIL);
}

int	executing_special_built_in(t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(&env, cmd));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(&env, cmd));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd, &env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd, 0));
	return (0);
}
