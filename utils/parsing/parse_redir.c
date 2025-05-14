/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:25:23 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/04 12:25:33 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

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

char	**tab_join(t_parse_redir *redir)
{
	int				i;
	int				index;
	char			**tab;
	t_parse_redir	*current;

	current = redir;
	index = 0;
	tab = malloc(sizeof(char *) * (len_list(redir) + 1));
	while (current != NULL)
	{
		i = 0;
		while (current->line[i] != NULL)
		{
			tab[index] = ft_strdup(current->line[i]);
			i++;
			index++;
		}
		current = current->next;
	}
	return (tab);
}

void	parse_lst_redir_char(t_parse_redir *redir)
{
	char			**line_temp;
	t_parse_redir	*temp;
	t_parse_redir	*current;

	current = redir;
	while (current != NULL)
	{
		temp = init_redir();
		tab_to_redir_char(temp, current->line, '<');
		line_temp = tab_join(temp);
		clean_split(current->line);
		current->line = ft_strdup_split(line_temp);
		clean_split(line_temp);
		clean_redir(temp);
		current = current->next;
	}
}

void	parse_lst_redir_str(t_parse_redir *redir, char *sep)
{
	char			**line_temp;
	t_parse_redir	*temp;
	t_parse_redir	*current;

	current = redir;
	while (current != NULL)
	{
		temp = init_redir();
		tab_to_redir_str(temp, current->line, sep);
		line_temp = tab_join(temp);
		clean_split(current->line);
		current->line = ft_strdup_split(line_temp);
		clean_split(line_temp);
		clean_redir(temp);
		current = current->next;
	}
}

void	parse_redir(t_parse_redir *redir, char **pipe)
{
	tab_to_redir_char(redir, pipe, '>');
	parse_lst_redir_char(redir);
	parse_lst_redir_str(redir, ">>");
	parse_lst_redir_str(redir, "<<");
}
