/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:57:22 by lidbaha           #+#    #+#             */
/*   Updated: 2025/04/01 13:57:52 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

void	add_quote(t_quotes *head, char *line, int index)
{
	t_quotes	*temp;

	if (head->line == NULL)
	{
		head->line = ft_strdup(line);
		head->index = index;
		head->next = NULL;
		return ;
	}
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = malloc(sizeof(t_quotes));
	temp->next->line = ft_strdup(line);
	temp->next->index = index;
	temp->next->next = NULL;
}

char	*remove_q(char *line, int i, int j)
{
	char	*tmp;
	int		k;

	k = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(line) - (j - i)));
	while (k < i)
	{
		tmp[k] = line[k];
		k++;
	}
	while (line[j] != '\0')
	{
		tmp[k] = line[j];
		k++;
		j++;
	}
	tmp[k] = '\0';
	return (tmp);
}

char	*remove_quotes(char *line, t_quotes *quotes)
{
	int			i;
	int			j;
	int			index;
	t_quotes	*head;

	i = 0;
	index = 0;
	head = quotes;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			j = i + 1;
			while (line[j] != '\0' && line[j] != line[i])
				j++;
			if (line[j] == '\0')
				break ;
			add_quote(head, ft_substr(line, i, j - i + 1), index + i);
			line = remove_q(line, i, j + 1);
			index += j - i + 1;
			i = -1;
		}
		i++;
	}
	return (line);
}
