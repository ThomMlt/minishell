/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:18:37 by thomas            #+#    #+#             */
/*   Updated: 2025/06/13 15:57:52 by tmillot          ###   ########.fr       */
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

static void	add_var_to_env(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new_node;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value != NULL)
				free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		prev = current;
		current = current->next;
	}
	new_node = new_node_env(key, value);
	if (prev)
		prev->next = new_node;
	else
		*env = new_node;
}

void	print_export_error(char *before)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(before, 2);
	ft_putstr_fd("\'", 2);
	ft_putstr_fd(" :not a valid identifier\n", 2);
}

static int	add_export(t_env **env, t_cmd *cmd)
{
	int		i;
	char	*before;
	char	*after;

	i = 1;
	while (cmd->args[i])
	{
		before = get_before_egal(cmd->args[i]);
		after = get_after_egal(cmd->args[i]);
		if (name_var_valid(before) == 0)
		{
			if (before == NULL)
				before = ft_strdup("=");
			print_export_error(before);
			return (free(before), free(after), EXIT_FAILURE);
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
	t_env	*sorted;
	t_env	*head_sorted;
	int		exit_status;

	exit_status = CODE_SUCCESS;
	if (cmd->args[1] == NULL)
	{
		sorted = sort_t_env(copy_export(*env));
		head_sorted = sorted;
		while (sorted)
		{
			if (sorted->value != NULL)
				printf("declare -x %s=\"%s\"\n", sorted->key, sorted->value);
			else
				printf("declare -x %s\n", sorted->key);
			sorted = sorted->next;
		}
		free_env(&head_sorted);
	}
	else
		exit_status = add_export(env, cmd);
	return (exit_status);
}
