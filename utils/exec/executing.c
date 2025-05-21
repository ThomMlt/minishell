/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 22:16:30 by thomas            #+#    #+#             */
/*   Updated: 2025/05/21 17:11:09 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
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
	while (current != NULL)
	{
		if (is_built_in(current->args[0]) == SUCCESS)
			current->builtin = true;
		else
			current->builtin = false;
		current = current->next;
	}
}

int	wait_children(int status)
{
	int		cur_status;
	int		final_status;
	pid_t	prev_pid;
	pid_t	cur_pid;

	final_status = status;
	prev_pid = waitpid(-1, &cur_status, 0);
	while (prev_pid > 0)
	{
		cur_pid = waitpid(-1, &cur_status, 0);
		if (prev_pid < cur_pid)
			final_status = cur_status;
		prev_pid = cur_pid;
	}
	if (final_status == 131)
		ft_putstr_fd("quit (core dumped)\n", 2);
	ft_printf("Salut !\n");
	return (final_status % 255);
}

// int	wait_children(void)
// {
// 	int	status;
// 	int	last_code = 0;
// 	pid_t	pid;

// 	while ((pid = waitpid(-1, &status, 0)) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			last_code = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 			last_code = 128 + WTERMSIG(status);
// 	}

// 	return (last_code);
// }

int	ft_exec(t_cmd *cmd, t_env *env, int last_status)
{
	int		pipe_fd[2];
	int		prev_fd;

	find_built_in(cmd);
	expand_and_trim_cmd(cmd, env, last_status);
	print_cmd_debug(cmd); // a supprimer 
	if (cmd->next == NULL && is_built_in(cmd->args[0]) == SUCCESS)
		return (exec_builtin(cmd, env));
	last_status = EXIT_SUCCESS;
	prev_fd = STDIN_FILENO;
	while (cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe error"), EXIT_FAILURE);
		last_status = ft_process(cmd, env, pipe_fd, prev_fd);
		close(pipe_fd[1]);
		if (prev_fd != 0)
			close(prev_fd);
		if (cmd->next != NULL)
			prev_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		cmd = cmd->next;
	}
	return (ft_exit_exec(cmd), wait_children(last_status));
}

/* attention redirection meme quand il n'y a pas de pipe car special bulting ne gere pas les redirection 
gerer les signaux, fonctions qui ecoutent les signaux dans les processus enfants dans exec child
rehinitialiser les redirection dans la sortie standard sinon ca ecrit dans le fichier out ou in */