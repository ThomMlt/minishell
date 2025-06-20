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

char	**ft_strdup_split(char **tab)
{
	int		len;
	char	**new_tab;
	int		i;
	int		j;

	len = ft_split_len(tab);
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	j = 0;
	while (j < len + 1)
	{
		new_tab[j] = NULL;
		j++;
	}
	i = 0;
	while (i < len)
	{
		if (tab[i])
			new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
