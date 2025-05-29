/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmillot <tmillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:16:40 by tmillot           #+#    #+#             */
/*   Updated: 2025/05/29 10:30:12 by tmillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../core/minishell.h"

volatile bool	g_signal = false;

void	signal_handler(int signum)
{
	printf("\n");
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
	sa_sigint.sa_handler = &signal_handler;
	if (sig == 1)
		sa_sigquit.sa_handler = SIG_IGN;
	else
		sa_sigquit.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
