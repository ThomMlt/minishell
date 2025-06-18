/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:16:40 by tmillot           #+#    #+#             */
/*   Updated: 2025/06/16 18:16:29 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

volatile bool	g_signal = false;

void	signal_handler(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (signum == SIGINT)
		g_signal = true;
}

void	signal_handler_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = true;
		write(1, "\n", 1);
	}
}

void	signal_handler_exec(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_signal = true;
	}
}

void	setup_signal_heredoc(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = signal_handler_here_doc;
	sigemptyset(&sa_sigint.sa_mask);
	sa_sigint.sa_flags = 0;
	sa_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_flags = 0;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	setup_signal(int sig)
{
	static struct sigaction	sa_sigint;
	static struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = SA_RESTART;
	sa_sigquit.sa_flags = SA_RESTART;
	sigemptyset(&sa_sigint.sa_mask);
	sigemptyset(&sa_sigquit.sa_mask);
	if (sig == 0)
	{
		sa_sigint.sa_handler = signal_handler;
		sa_sigquit.sa_handler = SIG_IGN;
	}
	else if (sig == 1)
	{
		sa_sigint.sa_handler = signal_handler_exec;
		sa_sigquit.sa_handler = signal_handler_exec;
	}
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
