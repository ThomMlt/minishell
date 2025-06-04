/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:33 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/29 13:19:49 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		setup_signal(1);
		line = readline("Minishell:~$ ");
		if (g_signal == true)
		{
			last_status = 130;
			g_signal = false;
		}
		add_history(line);
		cmd = init_cmd();
		parse(line, cmd);
		last_status = ft_exec(cmd, &env, last_status);
		free(line);
	}
}
