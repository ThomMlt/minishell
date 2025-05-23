/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:32:36 by toto              #+#    #+#             */
/*   Updated: 2025/05/12 17:43:45 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hexa_lowercase(int nb, int *count)
{
	const char			*base_hexa;
	int					i;
	char				stock[16];
	unsigned int		n;

	n = nb;
	i = 0;
	base_hexa = "0123456789abcdef";
	if (n == 0)
		(*count) += write(1, "0", 1);
	while (n > 0)
	{
		stock[i++] = base_hexa[n % 16];
		n = n / 16;
	}
	while (i > 0)
		(*count) += write(1, &stock[--i], 1);
}

void	ft_putnbr_hexa_uppercase(int nb, int *count)
{
	const char			*base_hexa;
	int					i;
	char				stock[16];
	unsigned int		n;

	n = nb;
	i = 0;
	base_hexa = "0123456789ABCDEF";
	if (n == 0)
		(*count) += write(1, "0", 1);
	while (n > 0)
	{
		stock[i++] = base_hexa[n % 16];
		n = n / 16;
	}
	while (i > 0)
		(*count) += write(1, &stock[--i], 1);
}
