/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/07/19 10:52:02 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_signal;

static void	sigint_handler(int signal);

/* 
 * Handling CTRL + D when NULL input.
 */
void	handle_ctrl_d(char *input)
{
	if (input == NULL)
	{
		printf("exit\n");
		exit(0);
	}
}

/*
 * Restores the default behaviour of the signal in the child process
 */
void	restore_signals(void)
{
	struct sigaction	sa_default;

	sa_default.sa_handler = SIG_DFL;
	ft_sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = 0;
	sigaction(SIGINT, &sa_default, NULL);
	sigaction(SIGQUIT, &sa_default, NULL);
}

/*
 * Ignores SIGINT y SIGQUIT signals int the main shell 
 * while it waits the child process.
 */
void	ignore_signals(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	ft_sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, NULL);
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

/*
 * Inicializar señales en la shell principal.
 */
void	signal_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	ft_sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	ft_sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
 * SIGINT (CTRL+C) handling.
 */
static void	sigint_handler(int signal)
{
	(void)signal;
	if (g_signal == S_INIT)
	{
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = S_INIT;
	}
	else if (g_signal == S_CMD)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_INIT;
	}
	else if (g_signal == S_HEREDOC)
	{
		g_signal = S_HEREDOC_MID;
		ioctl(0, TIOCSTI, "\n");
	}
}
