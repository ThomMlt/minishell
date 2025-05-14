/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:26:36 by lidbaha           #+#    #+#             */
/*   Updated: 2025/03/26 19:34:07 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] == c)
		{
			i += 2;
			continue ;
		}
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && (s[i] != c || (s[i] == c && s[i + 1] == c)))
				i++;
			count++;
		}
	}
	return (count);
}

static int	skip_double_sep(const char *s, char c, int i)
{
	if (s[i] == c && s[i + 1] == c)
		return (i + 2);
	return (i);
}

static int	fill_tab(char **tab, const char *s, char c, int *i, int y)
{
	int	start;

	while (s[*i] && s[*i] == c)
		(*i)++;
	start = *i;
	while (s[*i] && (s[*i] != c || (s[*i] == c && s[*i + 1] == c)))
		*i = skip_double_sep(s, c, *i) + 1;
	if (*i > start)
	{
		tab[y] = ft_substr(s, start, *i - start);
		if (!tab[y])
			return (0);
	}
	return (1);
}

static int	ft_copy_str_tab(char **tab, const char *s, char c)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s[i])
	{
		if (!fill_tab(tab, s, c, &i, y))
		{
			free_tab(tab, y - 1);
			return (0);
		}
		y++;
	}
	tab[y] = NULL;
	return (1);
}

char	**ft_minishell_split_char(const char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	if (!ft_copy_str_tab(tab, s, c))
		return (NULL);
	return (tab);
}
