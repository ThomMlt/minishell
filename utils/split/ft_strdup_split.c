/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:07:13 by lidbaha           #+#    #+#             */
/*   Updated: 2025/03/25 15:27:59 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	ft_split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	**ft_strdup_split(char **split)
{
	char	**new;
	int		i;

	if (!split)
		return (NULL);
	new = malloc(sizeof(char *) * (ft_split_len(split) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (split[i])
	{
		new[i] = ft_strdup(split[i]);
		if (!new[i])
		{
			clean_split(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}
