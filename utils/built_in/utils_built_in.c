/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:18:04 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/09 14:12:05 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	count_tab_char(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

t_env	*copy_export(t_env *env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	t_env	*cur_env;

	cur_env = env;
	head = NULL;
	current = NULL;
	new_node = NULL;
	while (cur_env != NULL)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->key = ft_strdup(cur_env->key);
		new_node->value = ft_strdup(cur_env->value);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		cur_env = cur_env->next;
	}
	return (head);
}

int	name_var_valid(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
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

t_env	*new_node_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}
