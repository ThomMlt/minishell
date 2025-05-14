/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:00:28 by tmillot           #+#    #+#             */
/*   Updated: 2025/03/20 11:12:55 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t size)
{
	char		*dup;
	size_t		i;
	size_t		len;

	i = 0;
	len = 0;
	while (len < size && s[len])
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (!dup)
		return (0);
	if (size == 0)
		return (0);
	while (s[i] && i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
