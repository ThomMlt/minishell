/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:44:12 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/13 15:57:58 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

void	command_not_found(char *cmd)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Command not found\n", 2);
}

void	no_such_file_or_directory(char *cmd)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	permission_denied(char *file)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

void	error_message(char *str)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	perror(str);
}

void	is_a_directory(char *str)
{
	ft_putstr_fd("Minishell:~$ ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}
