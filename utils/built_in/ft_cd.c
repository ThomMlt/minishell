/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:56:32 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:57:48 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static void	update_pwd(t_env **env, char *oldpwd)
{
	t_env	*current;
	char	newpwd[4096];

	current = *env;
	getcwd(newpwd, sizeof(newpwd));
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(newpwd);
		}
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(oldpwd);
		}
		current = current->next;
	}
}

static char	*find_home(t_env **env)
{
	t_env	*current;
	char	*find;

	current = *env;
	find = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 4) == 0)
		{
			find = ft_strdup(current->value);
			return (find);
		}
		current = current->next;
	}
	return (find);
}

static void	error_cd(char *message, int type)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(message, 2);
	if (type == 1)
		ft_putstr_fd(": No such file or directory", 2);
	if (type == 2)
		ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
}

int	ft_cd(t_env **env, t_cmd *cmd)
{
	int		nb_args;
	char	currentpwd[4096];
	char	*path;

	nb_args = count_tab_char(cmd->args);
	path = NULL;
	getcwd(currentpwd, sizeof(currentpwd));
	if (nb_args > 2)
		return (error_cd("too many arguments", 0), CODE_FAIL);
	if (nb_args == 2)
		path = ft_strdup(cmd->args[1]);
	if (nb_args == 1)
	{
		path = find_home(env);
		if (path == NULL)
			return (error_cd("HOME not set", 0), CODE_FAIL);
	}
	if (access(path, F_OK) == -1)
		return (error_cd(path, 1), free(path), CODE_FAIL);
	else if (access(path, W_OK) == -1)
		return (error_cd(path, 2), free(path), CODE_FAIL);
	if (chdir(path) == -1)
		perror("minishell: cd");
	return (update_pwd(env, currentpwd), free(path), CODE_SUCCESS);
}
