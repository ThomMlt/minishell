/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:31:12 by lidbaha           #+#    #+#             */
/*   Updated: 2025/04/11 13:39:26 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"
#include "../../includes/libft/libft.h"

static int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (i > 1)
		return (1);
	return (0);
}

static int	count_n_options(char **args)
{
	int	count;
	int	i;

	count = 0;
	i = 1;
	while (args[i] != NULL && is_valid_n_option(args[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_echo(t_cmd *cmd)
{
	int	n_options;
	int	i;
	int	first_arg;

	n_options = count_n_options(cmd->args);
	i = 1 + n_options;
	first_arg = 1;
	while (cmd->args[i])
	{
		if (first_arg == 0)
			write(1, " ", 1);
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		first_arg = 0;
		i++;
	}
	if (n_options == 0)
		write(1, "\n", 1);
	return (CODE_SUCCESS);
}

/*int main(int ac, char **av)
{
    t_cmd *commande;
    int i;
    commande = malloc(sizeof(t_cmd));
    commande->args = malloc(sizeof(char *) * (ac));
	i = 0;
	while (i < ac)
	{
		commande->args[i] = av[i + 1];
		printf("args[%d] = %s \n", i, commande->args[i]);
		i++;
	}
    commande->args[ac] = NULL;
    ft_echo(commande);
    free(commande->args);
    free(commande);
    return 0;
}*/