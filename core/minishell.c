/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:33 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/16 21:42:19 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_minishell(t_env **env, t_cmd *cmd, char *line)
{
	ft_putstr_fd("exit\n", 1);
	free_t_cmd(cmd);
	free_env(env);
	free(line);
}

static int	signal_to_false(int last_status)
{
	if (g_signal == true)
	{
		g_signal = false;
		return (130);
	}
	return (last_status);
}

void	arg(int argc, char **argv)
{
	if (argc > 1)
	{
		printf(ERR_NO_ARG);
		exit(EXIT_FAILURE);
	}
	(void)argv;
}

static int	process_command(char *line, t_cmd *cmd,
	t_env **env, int last_status)
{
	int	parsing_status;

	add_history(line);
	parsing_status = parse(line, cmd);
	if (parsing_status == 0)
		last_status = ft_exec(cmd, env, last_status);
	else if (line == NULL)
	{
		exit_minishell(env, cmd, line);
		exit(last_status);
	}
	else
	{
		last_status = parsing_status;
		free_t_cmd(cmd);
	}
	free(line);
	return (last_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_cmd	*cmd;
	int		status;
	int		last_status;

	arg(argc, argv);
	env = cpy_env(envp);
	last_status = 0;
	while (1)
	{
		setup_signal(0);
		line = readline("Minishell:~$ ");
		status = signal_to_false(last_status);
		if (status != 1)
		{
			last_status = status;
		}
		cmd = init_cmd();
		last_status = process_command(line, cmd, &env, last_status);
	}
}
