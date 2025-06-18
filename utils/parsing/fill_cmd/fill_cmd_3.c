/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:11:05 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/17 14:11:23 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

void	fill_t_cmd_next(t_cmd *current_cmd)
{
	current_cmd->next = init_cmd();
	current_cmd->next->prev = current_cmd;
}

void	fill_line_next(t_parse_redir *c_redir, t_cmd *current_cmd, int i)
{
	current_cmd->args = ft_divide_char_all(c_redir->line[i], ' ');
	remove_space(current_cmd);
}

int	fill_line_n(t_cmd *current_cmd, t_parse_redir *current_redir)
{
	int	status;

	while (current_redir != NULL)
	{
		if (current_redir->line[0][0] != '|')
		{
			status = fill_line(current_redir, current_cmd);
			if (status != 0)
				return (status);
			if (current_redir->next != NULL)
			{
				fill_t_cmd_next(current_cmd);
				current_cmd = current_cmd->next;
			}
			else
				current_cmd->next = NULL;
			current_redir = current_redir->next;
		}
		else if (current_redir->next != NULL)
			current_redir = current_redir->next;
	}
	return (0);
}
