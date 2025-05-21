/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:33 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/17 20:34:14 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	int		last_status;

	env = cpy_env(envp);
	last_status = 0;
	if (ac > 1)
	{
		printf("error, don't entry argument");
		return (0);
	}
	(void)av;
	while (1)
	{
		line = readline("Minishell:~$ ");
		add_history(line);
		last_status = parse_v2(line, env, last_status);
		free(line);
	}
	(void)env;
	return (0);
}
