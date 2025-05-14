/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:13:10 by thomas            #+#    #+#             */
/*   Updated: 2025/04/11 13:48:58 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

static void	rm_node(char *to_rm, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, to_rm) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_cmd *cmd, t_env **env)
{
	int		i;

	i = 1;
	while (cmd->args[i] != NULL)
	{
		rm_node(cmd->args[i], env);
		i++;
	}
	return (CODE_SUCCESS);
}

/*int main(int ac, char **av, char **env)
{
	t_env *envp;

	envp = cpy_env(env);
	t_cmd *commande_unset;
    int i;
    commande_unset = malloc(sizeof(t_cmd));
    commande_unset->args = malloc(sizeof(char *) * (ac));
	i = 0;
	while (i < ac)
	{
		commande_unset->args[i] = av[i + 1];
		i++;
	}
	commande_unset->args[ac] = NULL;
	ft_unset(commande_unset, &envp);
	t_cmd *commande_env;
    commande_env = malloc(sizeof(t_cmd));
    commande_env->args = malloc(sizeof(char *) * (2));
	char *truc = "env";
	commande_env->args[0] = truc;
	commande_env->args[1] = NULL;
	ft_env(envp, commande_env);
}*/