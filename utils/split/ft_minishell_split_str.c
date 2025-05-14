/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:58:52 by lidbaha           #+#    #+#             */
/*   Updated: 2025/03/29 06:16:21 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static int	count_word(const char *s, char *sep)
{
	int		count;
	size_t	sep_len;

	count = 0;
	sep_len = ft_strlen(sep);
	while (*s)
	{
		while (*s && ft_strncmp(s, sep, sep_len) == 0)
			s += sep_len;
		if (*s)
		{
			count++;
			while (*s && ft_strncmp(s, sep, sep_len) != 0)
				s++;
		}
	}
	return (count);
}

static char	*copy_str(const char *s, int start, int end)
{
	return (ft_substr(s, start, end - start));
}

static int	ft_copy_str_tab(char **tab, const char *s, char *sep)
{
	int			i;
	const char	*next_sep;

	i = 0;
	while (*s)
	{
		while (*s && ft_strncmp(s, sep, ft_strlen(sep)) == 0)
			s += ft_strlen(sep);
		if (*s)
		{
			next_sep = strstr(s, sep);
			if (!next_sep)
				next_sep = s + ft_strlen(s);
			tab[i] = copy_str(s, 0, next_sep - s);
			if (!tab[i])
				return (free_tab(tab, i - 1), 0);
			i++;
			s = next_sep;
		}
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_minishell_split_str(const char *s, char *sep)
{
	char	**tab;

	if (!s || !sep)
		return (NULL);
	tab = malloc((count_word(s, sep) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (!ft_copy_str_tab(tab, s, sep))
		return (NULL);
	return (tab);
}
