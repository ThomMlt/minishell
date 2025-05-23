/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speciale_built_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:06:03 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/23 04:08:02 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	is_special_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(cmd, "export") == 0)
		return (SUCCESS);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (SUCCESS);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (SUCCESS);
	else
		return (FAIL);
}
