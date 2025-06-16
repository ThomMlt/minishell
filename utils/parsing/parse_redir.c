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

#include "../../core/minishell.h"

char	**tab_join(t_parse_redir *redir)
{
	int				i;
	int				j;
	int				index;
	char			**tab;
	t_parse_redir	*current;

	current = redir;
	index = 0;
	tab = malloc(sizeof(char *) * (len_list(redir) + 1));
	j = -1;
	while (++j < len_list(redir) + 1)
		tab[j] = NULL;
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

void	remove_redir_spaces(t_parse_redir *redir)
{
	t_parse_redir	*current_redir;
	char			**new;
	int				size;
	int				i;

	current_redir = redir;
	while (current_redir != NULL)
	{
		i = 0;
		size = 0;
		while (current_redir->line[i] != NULL)
		{
			if (!is_only_spaces(current_redir->line[i]))
				size++;
			i++;
		}
		new = malloc(sizeof(char *) * (size + 1));
		i = 0;
		size = 0;
		while (current_redir->line[i] != NULL)
		{
			if (!is_only_spaces(current_redir->line[i]))
			{
				new[size] = ft_strdup(current_redir->line[i]);
				size++;
			}
			i++;
		}
		new[size] = NULL;
		clean_split(current_redir->line);
		current_redir->line = ft_strdup_split(new);
		clean_split(new);
		current_redir = current_redir->next;
	}
}

void	parse_redir(t_parse_redir *redir, char **pipe)
{
	tab_to_redir_char(redir, pipe, '>');
	parse_lst_redir_char(redir);
	parse_lst_redir_str(redir, ">>");
	parse_lst_redir_str(redir, "<<");
	remove_redir_spaces(redir);
}
