/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:05:42 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/14 19:17:25 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

int	ft_pwd(void)
{
	char	buffer[4096];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("getcwd");
		return (CODE_FAIL);
	}
	ft_putstr_fd(buffer, 1);
	ft_putchar_fd('\n', 1);
	return (CODE_SUCCESS);
}
