/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:33 by lidbaha           #+#    #+#             */
/*   Updated: 2025/06/10 21:09:38 by tmillot          ###   ########.fr       */
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

static int	signal_to_false(void)
{
	if (g_signal == true)
		g_signal = false;
	return (130);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_cmd	*cmd;
	int		last_status;

	env = cpy_env(envp);
	last_status = 0;
	if (argc > 1)
		return (printf(ERR_NO_ARG), 0);
	(void)argv;
	while (1)
	{
		setup_signal(0);
		line = readline("Minishell:~$ ");
		if (g_signal == true)
			last_status = signal_to_false();
		add_history(line);
		cmd = init_cmd();
		if (parse(line, cmd) == 0)
			last_status = ft_exec(cmd, &env, last_status);
		else if (line == NULL)
			return (exit_minishell(&env, cmd, line), last_status);
		else
			free_t_cmd(cmd);
		free(line);
	}
}
