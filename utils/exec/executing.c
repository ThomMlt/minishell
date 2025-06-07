/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:16:30 by thomas            #+#    #+#             */
/*   Updated: 2025/06/06 12:18:36 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

const char *token_type_to_str(t_token_type type)
{
	if (type == REDIRECT_IN)
		return ("<");
	if (type == REDIRECT_OUT)
		return (">");
	if (type == REDIRECT_APPEND)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	return ("UNKNOWN");
}

void	print_redirs(t_redir *redir, const char *label)
{
	int	i = 0;

	printf("  └─ %s redirs:\n", label);
	while (redir)
	{
		printf("     [%d] type: %-7s | file: \"%s\"\n",
			i++, token_type_to_str(redir->type),
			redir->file ? redir->file : "(null)");
		redir = redir->next;
	}
	if (i == 0)
		printf("     [empty]\n");
}

void	print_args(char **args)
{
	int i = 0;

	if (!args)
	{
		printf("  └─ args: NULL\n");
		return;
	}
	printf("  └─ args:\n");
	while (args[i])
	{
		printf("     [%d] \"%s\"\n", i, args[i]);
		i++;
	}
	if (i == 0)
		printf("     [empty args]\n");
}

void	print_cmd_list(t_cmd *cmd)
{
	int index = 0;
	t_cmd *current = cmd;

	while (current)
	{
		printf("🔹 Node %d of t_cmd:\n", index++);
		print_args(current->args);
		print_redirs(current->infile, "infile");
		print_redirs(current->outfile, "outfile");
		printf("  └─ builtin: %s\n", current->builtin ? "true" : "false");
		printf("  └─ pid: %d\n", current->pid);
		printf("  └─ has prev: %s | has next: %s\n",
			current->prev ? "yes" : "no", current->next ? "yes" : "no");
		printf("────────────────────────────────────────\n");
		current = current->next;
	}
}

int	is_built_in(char *str)
{
	if (str == NULL)
		return (FAIL);
	else if (ft_strcmp(str, "echo") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "cd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "env") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "exit") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "export") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "pwd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "unset") == 0)
		return (SUCCESS);
	else
		return (FAIL);
}

static void	find_built_in(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		if (is_built_in(current->args[0]) == SUCCESS)
			current->builtin = true;
		else
			current->builtin = false;
		current = current->next;
	}
}

int	wait_children(int status, t_cmd *cmd)
{
	t_cmd	*current;
	int		last_status;
	int		cur_status;
	int		signal_num;

	current = cmd;
	last_status = status;
	cur_status = 0;
	while (current != NULL)
	{
		waitpid(current->pid, &cur_status, 0);
		if (WIFEXITED(cur_status))
			last_status = WEXITSTATUS(cur_status);
		else if (WIFSIGNALED(cur_status))
		{
			signal_num = WTERMSIG(cur_status);
			// if (signal_num == SIGINT)
			// 	write(1, "\n", 1);
			if (signal_num == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19);
			last_status = 128 + signal_num;
		}
		current = current->next;
	}
	return (free_t_cmd(cmd), last_status % 255);
}

int	is_special_build_in_parent(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd[0], "export", 7) == 0
		|| ft_strncmp(cmd[0], "unset", 6) == 0
		|| ft_strncmp(cmd[0], "exit", 5) == 0)
		return (0);
	return (1);
}

int	ft_exec(t_cmd *cmd, t_env **env, int last_status)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_fd;

	find_built_in(cmd);
	expand_and_trim_cmd(cmd, env, last_status);
	prev_fd = STDIN_FILENO;
	current = cmd;
	setup_signal(1);
	if (current->next == NULL && is_special_build_in_parent(current->args) == 0)
		return (exec_builtin(current, env), free_t_cmd(current), 0);
	while (current != NULL)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe error"), EXIT_FAILURE);
		last_status = ft_process(current, env, pipe_fd, prev_fd);
		close(pipe_fd[1]);
		if (prev_fd != 0)
			close(prev_fd);
		if (current->next != NULL)
			prev_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		current = current->next;
	}
	return (wait_and_free(last_status, cmd));
}
