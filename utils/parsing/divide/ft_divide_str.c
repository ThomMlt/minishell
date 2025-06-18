/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lidbaha <lidbaha@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:37:08 by lidbaha           #+#    #+#             */
/*   Updated: 2025/05/13 21:38:09 by lidbaha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

char	**ft_divide_str(char *line, char *sep)
{
	char	**result;

	result = malloc(sizeof(char *) * (divide_size_str(line, sep) * 2 + 2));
	if (!result)
		return (NULL);
	divide_str(line, result, sep);
	return (result);
}
