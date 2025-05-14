/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:37:08 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/13 21:38:09 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

int	is_separator_at(char *line, char *sep, int pos)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		if (line[pos + i] != sep[i])
			return (0);
		i++;
	}
	return (1);
}

int	divide_size_str(char *line, char *sep)
{
	int	i;
	int	result;
	int	sep_len;

	i = 0;
	result = 0;
	sep_len = ft_strlen(sep);
	if (sep_len == 0)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quote_closed(line, i + 1, line[i]) + 1;
		else if (is_separator_at(line, sep, i) && !is_separator_at(line, sep, i + sep_len))
		{
			result++;
			i += sep_len - 1;
		}
		else
			i++;
	}
	return (result);
}

char	*add_sep_str(char *sep)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(sep);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (sep[i])
	{
		result[i] = sep[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*add_chunk_str(char *line, int start, int end)
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

void	divide_str(char *line, char **result, char *sep)
{
	int	i;
	int	start;
	int	index;
	int	sep_len;

	i = 0;
	start = 0;
	index = 0;
	sep_len = ft_strlen(sep);
	while (line[i] != '\0')
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = check_quote_closed(line, i + 1, line[i]) + 1;
		else if (is_separator_at(line, sep, i) && !is_separator_at(line, sep, i + sep_len))
		{
			result[index] = add_chunk_str(line, start, i - 1);
			result[index + 1] = add_sep_str(sep);
			start = i + sep_len;
			index += 2;
			i += sep_len - 1;
		}
		else
			i++;
	}
	if (start < i)
	{
		result[index] = add_chunk_str(line, start, i - 1);
		index++;
	}
	result[index] = NULL;
}

char	**ft_divide_str(char *line, char *sep)
{
	char	**result;

	result = malloc(sizeof(char *) * (divide_size_str(line, sep) * 2 + 2));
	if (!result)
		return (NULL);
	divide_str(line, result, sep);
	return (result);
}
