/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_char_all.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 23:02:08 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/11 23:02:49 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

void	divide_all(char *line, char **result, char sep)
{
	int	i;
	int	start;
	int	index;

	i = -1;
	start = 0;
	index = 0;
	while (line[++i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quote_closed(line, i + 1, line[i]);
		if (line[i] == sep)
		{
			if (i != 0)
			{
				if (line[i - 1] != sep)
				{
					result[index] = add_chunk(line, start, i - 1);
					index++;
				}
			}
			start = i + 1;
		}
	}
	if (start < i && line[start] != sep)
	{
		result[index] = add_chunk(line, start, i - 1);
		index++;
	}
	result[index] = NULL;
}

int	divide_size_all(char *line, char sep)
{
	int	i;
	int	word;
	int	result;

	i = 0;
	word = 0;
	result = 0;
	while (line[i] != '\0')
	{
		if (line[i] != sep)
			word = 1;
		else if (word == 1)
		{
			result++;
			word = 0;
		}
		i++;
	}
	if (word == 1)
		result++;
	return (result);
}

char	**ft_divide_char_all(char *line, char sep)
{
	char	**result;

	result = malloc(sizeof(char *) * (divide_size_all(line, sep) + 1));
	if (!result)
		return (NULL);
	divide_all(line, result, sep);
	return (result);
}
