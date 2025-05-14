/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:55:08 by lidbaha           #+#    #+#             */
/*   Updated: 2025/04/12 17:55:09 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

int	divide_size(char *line, char sep)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quote_closed(line, i + 1, line[i]) + 1;
		if (line[i] == sep && line[i + 1] != sep)
			result++;
		i++;
	}
	return (result);
}

char	*add_sep(char sep)
{
	char	*result;

	result = malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	result[0] = sep;
	result[1] = '\0';
	return (result);
}

char	*add_chunk(char *line, int start, int end)
{
	char	*chunk;
	int		i;

	i = 0;
	chunk = malloc(sizeof(char) * (end - start + 2));
	if (!chunk)
		return (NULL);
	while (start <= end)
	{
		chunk[i] = line[start];
		i++;
		start++;
	}
	chunk[i] = '\0';
	return (chunk);
}

void	divide(char *line, char **result, char sep)
{
	int	i;
	int	start;
	int	index;

	i = 0;
	start = 0;
	index = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quote_closed(line, i + 1, line[i]) + 1;
		if (line[i] == sep && line[i + 1] != sep && line[i - 1] != sep)

		{
			result[index] = add_chunk(line, start, i - 1);
			result[index + 1] = add_sep(sep);
			start = i + 1;
			index += 2;
		}
		i++;
	}
	if (start < i)
	{
		result[index] = add_chunk(line, start, i - 1);
		index++;
	}
	result[index] = NULL;
}

char	**ft_divide_char(char *line, char sep)
{
	char	**result;

	result = malloc(sizeof(char *) * (divide_size(line, sep) * 2 + 2));
	divide(line, result, sep);
	return (result);
}
