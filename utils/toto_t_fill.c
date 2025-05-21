/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toto_t_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:48:05 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/21 15:17:10 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/minishell.h"

#include <stdio.h>

static const char *get_redir_type_name(t_token_type type)
{
	if (type == REDIRECT_IN)
		return "<";
	else if (type == REDIRECT_OUT)
		return ">";
	else if (type == REDIRECT_APPEND)
		return ">>";
	else if (type == HEREDOC)
		return "<<";
	else
		return "UNKNOWN";
}

void	print_cmd_debug(t_cmd *cmd)
{
	int i = 0;
	int cmd_num = 1;

	while (cmd)
	{
		printf("========== COMMAND %d ==========\n", cmd_num++);

		// Print args
		printf("ARGS:\n");
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("  args[%d] = [%s]\n", i, cmd->args[i]);
				i++;
			}
		}
		else
			printf("  (null)\n");

		// Print input redirections
		printf("INFILES:\n");
		t_redir *in = cmd->infile;
		while (in)
		{
			printf("  type: %s\tfile: [%s]\n", get_redir_type_name(in->type), in->file);
			in = in->next;
		}

		// Print output redirections
		printf("OUTFILES:\n");
		t_redir *out = cmd->outfile;
		while (out)
		{
			printf("  type: %s\tfile: [%s]\n", get_redir_type_name(out->type), out->file);
			out = out->next;
		}

		// Print builtin flag
		printf("BUILTIN: %s\n", cmd->builtin ? "true" : "false");

		printf("\n");
		cmd = cmd->next;
		i = 0;
	}
}

void	debug_parse_redir(t_parse_redir *redir)
{
	int i;
	int node_num = 0;
	t_parse_redir *lst;

	lst = redir;
	while (lst)
	{
		printf("🔗 Node %d:\n", node_num);
		if (lst->line == NULL)
		{
			printf("  line: (NULL)\n");
		}
		else
		{
			i = 0;
			while (lst->line[i])
			{
				printf("  line[%d] = \"%s\"\n", i, lst->line[i]);
				i++;
			}
		}
		lst = lst->next;
		node_num++;
	}
}

void add_back_t_redir(t_redir **redirection, char *file, t_token_type type)
{
	t_redir		*new;
	t_redir		*current;

	new = malloc(sizeof(t_redir));
	if (type == HEREDOC)
		new->file = get_here_doc(file);
	else
		new->file = ft_strdup(file);
	new->type = type;
	new->next = NULL;
	current = *redirection;
	if (*redirection == NULL)
		*redirection = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

char	**list_to_array_char(t_list *lst)
{
	int		size;
	char	**tab;
	int		i;

	size = ft_lstsize(lst);
	i = 0;
	tab = malloc(sizeof(char *) * (size + 1));
	while (lst != NULL)
	{
		tab[i++] = lst->content;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	fill_t_cmd(t_parse_redir *redir, t_cmd *cmd)
{
	int				i;
	t_parse_redir	*current_redir;
	t_cmd			*current_cmd;

	current_redir = redir;
	current_cmd = cmd;
	debug_parse_redir(current_redir);
	while (current_redir != NULL)
	{
		i = 0;
		if (ft_strcmp_minishell(current_redir->line[0], "|") == 1)
			current_redir = current_redir->next;
		while (current_redir->line[i] != NULL)
		{
			if (ft_strcmp_minishell(current_redir->line[i], "<") == 1)
			{
				add_back_t_redir(&current_cmd->infile, current_redir->line[i + 1], REDIRECT_IN);
				i += 1;
			}
			else if (ft_strcmp_minishell(current_redir->line[i], ">") == 1)
			{
				add_back_t_redir(&current_cmd->outfile, current_redir->line[i + 1], REDIRECT_OUT);
				i += 1;
			}
			else if (ft_strcmp_minishell(current_redir->line[i], "<<") == 1)
			{
				add_back_t_redir(&current_cmd->infile, current_redir->line[i + 1], HEREDOC);
				i += 1;
			}
			else if (ft_strcmp_minishell(current_redir->line[i], ">>") == 1)
			{
				add_back_t_redir(&current_cmd->outfile, current_redir->line[i + 1], REDIRECT_APPEND);
				i += 1;
			}
			else if (ft_strcmp_minishell(current_redir->line[i], "") == 0)
			{
				current_cmd->args = ft_split(current_redir->line[i], ' ');
			}
			i++;
		}
		if (current_redir->next != NULL)
		{
			current_cmd->next = init_cmd();
			current_cmd = current_cmd->next;
		}
		else
			current_cmd->next = NULL;
		current_redir = current_redir->next;
	}
}
