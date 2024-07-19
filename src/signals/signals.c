// signals.c
#include "../../include/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

static void	sigint_handler(int sig);
static void signquit_handler(int sig);

int g_signal;

void signal_init(void)
{
    g_signal = S_BASE;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, signquit_handler);
}

void handle_ctrl_d(char *line)
{
    if (line == NULL)
    {
        printf("exit\n");
        exit(0);
    }
}

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == S_BASE || g_signal == S_SIGINT)
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
        ioctl(0, TIOCSTI, '\n');
		exit(0);
	}

	if (g_signal == S_HEREDOC_END)
		ft_putstr_fd("\n", 1);
}

static void signquit_handler(int sig)
{
	(void)sig;
	if (g_signal == S_CMD)
	{
		printf("Quit (core dump)\n");
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
	}
	else
	{
		printf(PROMPT);
	}
}
