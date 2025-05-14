/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:16:33 by toto              #+#    #+#             */
/*   Updated: 2025/05/12 17:43:49 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_count(char *str, int *count)
{
	int	i;

	i = 0;
	if (str == NULL)
		(*count) += write(1, "(null)", 6);
	while (str != NULL && str[i] != '\0')
	{
		(*count) += write(1, &str[i], 1);
		i++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
