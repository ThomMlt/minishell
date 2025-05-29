/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:55:42 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/26 11:57:53 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static char	*path_of_env(t_env **env)
{
	t_env	*current;
	char	*path;

	current = *env;
	path = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
		{
			path = ft_strdup(current->value);
			return (path);
		}
		current = current->next;
	}
	return (path);
}

char	*find_cmd_path(t_env **env, t_cmd *cmd)
{
	int		i;
	char	*path_env;
	char	*res;
	char	*cmd_slash;
	char	**possible_path;

	i = -1;
	path_env = path_of_env(env);
	cmd_slash = ft_strjoin("/", cmd->args[0]);
	if (access(cmd->args[0], F_OK | X_OK) == 0)
		return (free(path_env), free(cmd_slash), ft_strdup(cmd->args[0]));
	if (path_env == NULL)
		return (free(path_env), free(cmd_slash),
			command_not_found(cmd->args[0]), NULL);
	possible_path = ft_split(path_env, ':');
	while (possible_path[++i] != NULL)
	{
		res = ft_strjoin(possible_path[i], cmd_slash);
		if (access(res, F_OK | X_OK) == 0)
			return (free(cmd_slash), free(path_env),
				clean_split(possible_path), res);
		free(res);
	}
	command_not_found(cmd->args[0]);
	return (free(cmd_slash), free(path_env), clean_split(possible_path), NULL);
}
