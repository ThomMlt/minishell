/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:44:45 by tmillot           #+#    #+#             */
/*   Updated: 2025/03/31 18:22:01 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

char	*get_before_egal(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	len = i;
	res = ft_strndup(str, (size_t)len);
	return (res);
}

char	*get_after_egal(char *str)
{
	char	*egal;
	char	*res;

	egal = ft_strchr(str, '=');
	if (egal == NULL)
		return (NULL);
	if (*(egal + 1) == '\0')
		return (ft_strdup(""));
	res = ft_strdup(egal + 1);
	return (res);
}

t_env	*cpy_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	new_node = NULL;
	while (env[i] != NULL)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->key = get_before_egal(env[i]);
		new_node->value = get_after_egal(env[i]);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

/*int main(int ac, char **av, char **env)
{
	t_env *envp;

	envp = cpy_env(env);
	while (envp->next != NULL)
	{
		printf("key : %s\n", envp->key);
		printf("value : %s\n", envp->value);
		envp = envp->next;
	}
}*/