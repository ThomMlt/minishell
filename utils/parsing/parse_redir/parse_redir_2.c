/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:25:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/20 12:42:52 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

int	redir_space_size(t_parse_redir	*current_redir)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (current_redir->line[i] != NULL)
	{
		if (!is_only_spaces(current_redir->line[i]))
			size++;
		i++;
	}
	return (size);
}

t_parse_redir	*add_list(char **line)
{
	t_parse_redir	*dest;

	dest = malloc(sizeof(t_parse_redir));
	if (!dest)
		return (NULL);
	dest->line = ft_strdup_split(line);
	dest->next = NULL;
	return (dest);
}

void	tab_to_redir_char(t_parse_redir *redir, char **pipe, char sep)
{
	int				i;
	char			**temp;
	t_parse_redir	*current;

	i = 0;
	current = redir;
	while (pipe[i] != NULL)
	{
		temp = ft_divide_char(pipe[i], sep);
		if (current->line == NULL)
		{
			current->line = ft_strdup_split(temp);
			current->next = NULL;
		}
		else
		{
			while (current->next != NULL)
				current = current->next;
			current->next = add_list(temp);
		}
		clean_split(temp);
		i++;
	}
}

void	tab_to_redir_str(t_parse_redir *redir, char **pipe, char *sep)
{
	int				i;
	char			**temp;
	t_parse_redir	*current;

	i = 0;
	current = redir;
	while (pipe[i] != NULL)
	{
		temp = ft_divide_str(pipe[i], sep);
		if (current->line == NULL)
		{
			current->line = ft_strdup_split(temp);
			current->next = NULL;
		}
		else
		{
			while (current->next != NULL)
				current = current->next;
			current->next = add_list(temp);
		}
		clean_split(temp);
		i++;
	}
}

int	len_list(t_parse_redir *redir)
{
	int				i;
	int				len;
	t_parse_redir	*current;

	len = 0;
	current = redir;
	while (current != NULL)
	{
		i = 0;
		while (current->line[i] != NULL)
			i++;
		len += i;
		current = current->next;
	}
	return (len);
}
