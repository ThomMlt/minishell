/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:18:37 by thomas            #+#    #+#             */
/*   Updated: 2025/05/12 17:48:07 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static t_env	*sort_t_env(t_env *env)
{
	int		swapped;
	t_env	**ptr;
	t_env	*current;
	t_env	*next_node;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = &env;
		while (*ptr && (*ptr)->next)
		{
			current = *ptr;
			next_node = current->next;
			if (ft_strcmp(current->key, next_node->key) > 0)
			{
				current->next = next_node->next;
				next_node->next = current;
				*ptr = next_node;
				swapped = 1;
			}
			ptr = &(*ptr)->next;
		}
	}
	return (env);
}

int	name_var_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	add_var_to_env(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current->next)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	current->next = new_node;
}

static int	add_export(t_env **env, t_cmd *cmd)
{
	int		i;
	char	*before;
	char	*after;

	i = 1;
	while (cmd->args[i])
	{
		before = cmd->args[i];
		after = cmd->args[i];
		if (name_var_valid(before) == 0)
		{
			printf("minishell: export: '%s' :not a valid identifier",
				before);
			return (EXIT_FAILURE);
		}
		else
			add_var_to_env(before, after, env);
		free(after);
		free(before);
		i++;
	}
	return (CODE_SUCCESS);
}

int	ft_export(t_env **env, t_cmd *cmd)
{
	t_env	*cpy;
	int		exit_status;

	cpy = *env;
	exit_status = CODE_SUCCESS;
	if (cmd->args[1] == NULL && ft_strcmp(cmd->args[0], "export") == 0)
	{
		cpy = sort_t_env(cpy);
		while (cpy)
		{
			printf("declare -x %s=\"%s\"\n", cpy->key, cpy->value);
			cpy = cpy->next;
		}
	}
	else
		exit_status = add_export(env, cmd);
	return (exit_status);
}
