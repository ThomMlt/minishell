/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:23:13 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/25 14:23:59 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

char	**ft_strndup_split(char **tab, int i)
{
	int		len;
	char	**new_tab;
	int		j;

	len = ft_split_len(tab);
	new_tab = malloc(sizeof(char *) * ((len + 1) - i));
	if (!new_tab)
		return (NULL);
	j = 0;
	while (j < (len + 1) - i)
	{
		new_tab[j] = NULL;
		j++;
	}
	j = 0;
	while (i < len)
	{
		if (tab[i])
			new_tab[j] = ft_strdup(tab[i]);
		i++;
		j++;
	}
	new_tab[j] = NULL;
	return (new_tab);
}
