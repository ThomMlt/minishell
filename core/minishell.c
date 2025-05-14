/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:23:33 by lidbaha           #+#    #+#             */
/*   Updated: 2025/04/16 14:07:10 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;

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
		parse_v2(line);
		free(line);
	}
	(void)env;
	return (0);
}
