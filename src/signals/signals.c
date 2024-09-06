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
static void	sigquit_handler(int signal);

/*
 * Signal (CTRL + D, CTRL + C, CTRL + /) initialization.
 */
void	signal_init(void)
{
	g_signal = S_INIT;
	printf("%dAquie\n", g_signal);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

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
 * Handling SIGINT signal.
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
	}
	else if (g_signal == S_CMD)
	{
		ft_putstr_fd("\n", 1);
	}
	else if (g_signal == S_HEREDOC)
	{
		g_signal = S_HEREDOC_MID;
		ioctl(0, TIOCSTI, "\n");
	}
}

/*
 * Handling SIGQUIT signal.
 */
static void	sigquit_handler(int signal)
{
	(void)signal;printf("%d", g_signal);
	if (g_signal == S_CMD)
	{
		printf("Quit (core dump)\n");
		rl_on_new_line();
		g_signal = S_INIT;
	}
	else if(g_signal == S_CMD || g_signal == S_HEREDOC)
	{
		rl_replace_line("", 0);
		printf(PROMPT);
		g_signal = S_INIT;
	}
}
