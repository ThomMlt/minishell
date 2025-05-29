/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:10:09 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/23 19:28:25 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static int	size_struct_env(t_env **env)
{
	int		count;
	t_env	*current;

	current = *env;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*join_key_and_value(char *key, char *value)
{
	char	*res;
	int		i;
	int		j;

	res = malloc((ft_strlen(key) + ft_strlen(value) + 2) * sizeof(char));
	i = 0;
	j = 0;
	while (key[i] != '\0')
	{
		res[i] = key[i];
		i++;
	}
	res[i++] = '=';
	if (value != NULL)
		while (value[j] != '\0')
			res[i++] = value[j++];
	res[i] = '\0';
	return (res);
}

char	**env_tab_char(t_env **env, char *path_cmd)
{
	int		size;
	char	**tab_char;
	int		i;
	t_env	*current;

	if (path_cmd == NULL)
		return (NULL);
	size = size_struct_env(env);
	tab_char = malloc((size + 1) * sizeof(char *));
	i = 0;
	current = *env;
	while (current != NULL)
	{
		tab_char[i] = join_key_and_value(current->key, current->value);
		current = current->next;
		i++;
	}
	tab_char[i] = NULL;
	return (tab_char);
}
