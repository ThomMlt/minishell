/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:37:05 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/23 15:07:45 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static void	error_env(char *args)
{
	ft_putstr_fd("env: \'", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd("\': No such file or directory\n", 2);
}

int	ft_env(t_env **env, t_cmd *cmd)
{
	t_env	*current;

	current = *env;
	if (count_tab_char(cmd->args) > 1)
		return (error_env(cmd->args[1]), 127);
	while (current)
	{
		if (current->value != NULL)
		{
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
	return (CODE_SUCCESS);
}

/*int main(int ac, char **av, char **env)
{
	t_env *envp;

	envp = cpy_env(env);
	t_cmd *commande;
    int i;
    commande = malloc(sizeof(t_cmd));
    commande->args = malloc(sizeof(char *) * (ac));
	i = 0;
	while (i < ac)
	{
		commande->args[i] = av[i + 1];
		i++;
	}
	commande->args[ac] = NULL;

	ft_env(envp, commande);
}*/