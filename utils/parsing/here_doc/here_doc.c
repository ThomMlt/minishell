/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:46:35 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/16 19:52:23 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../core/minishell.h"

void	made_new_file(int *fd, char **name)
{
	static int	nb_file = 1;
	char		*str;
	char		*number_file;

	number_file = ft_itoa(nb_file);
	str = ft_strjoin("/tmp/here_doc_", number_file);
	*name = ft_strdup(str);
	*fd = open(*name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(str);
	free(number_file);
	nb_file++;
}

int	if_limiter(char *line, char *limiter)
{
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
		&& ft_strlen(limiter) == ft_strlen(line) - 1)
		return (0);
	return (1);
}

int	fill_here_doc_file(int fd, char *delimitor)
{
	char	*line;

	setup_signal_heredoc();
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (g_signal == true)
			return (free_path(line), 0);
		if (line == NULL)
		{
			ft_printf("bash: warning: here-document delimited"
				" by end-of-file (wanted `%s')\n", delimitor);
			break ;
		}
		if (if_limiter(line, delimitor) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	return (1);
}

char	*get_here_doc(char *str)
{
	char	*file_name;
	char	*delimitor;
	int		here_doc_fd;

	delimitor = ft_strdup(str);
	file_name = NULL;
	made_new_file(&here_doc_fd, &file_name);
	if (here_doc_fd == -1)
	{
		while (access(file_name, W_OK) == -1 || here_doc_fd == -1)
		{
			free(file_name);
			made_new_file(&here_doc_fd, &file_name);
		}
	}
	fill_here_doc_file(here_doc_fd, delimitor);
	free(delimitor);
	close(here_doc_fd);
	if (g_signal == true)
		return (free(file_name), NULL);
	return (file_name);
}
