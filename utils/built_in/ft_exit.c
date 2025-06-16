/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:52:14 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:57:51 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	ft_check_atoll(const char *str, int *err)
{
	int					neg;
	unsigned long long	res;
	int					i;

	res = 0;
	i = 0;
	neg = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			neg *= -1;
	}
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			res = (res * 10) + (str[i] - '0');
		else
			*err = -1;
		if ((neg == 1 && res > LL_MAX) || (neg == -1 && res > LL_MAX + 1))
			*err = -1;
		i++;
	}
	return ((int)((res * (unsigned long long)neg) % 256));
}

void	exit_code(t_cmd *cmd, t_env **env, int exit_code, int do_exit)
{
	if (do_exit == 0)
	{
		if (cmd != NULL)
		{
			free_t_cmd_nowhere(cmd);
			free_env(env);
		}
		exit(exit_code);
	}
}

int	ft_exit(t_cmd *cmd, t_env **env, int exit_status)
{
	int	err;
	int	size;

	size = count_tab_char(cmd->args);
	err = 0;
	ft_putstr_fd("exit\n", 1);
	if (size >= 2)
	{
		exit_status = ft_check_atoll(cmd->args[1], &err);
		if (err == -1)
		{
			ft_putstr_fd(ERR_NUM_EXIT, 2);
			return (exit_code(cmd, env, 2, 0), 2);
		}
		else if (err == 0 && size == 2)
			return (exit_code(cmd, env, exit_status, 0), exit_status);
		else
		{
			ft_putstr_fd(ERR_ARG_EXIT, 2);
			return (1);
		}
	}
	else
		return (exit_code(cmd, env, 0, 0), 0);
}
