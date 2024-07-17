// signals.c
#include "../../include/minishell.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/ioctl.h>

static void receive_signals(int signal);

int g_signal;

void signal_init(void)
{
    g_signal = S_INIT;
    signal(SIGINT, receive_signals);
    signal(SIGQUIT, SIG_IGN);
}

static void receive_signals(int signal)
{
    (void)signal;
    if (g_signal == S_INIT || g_signal == S_SIGINT)
    {
        ft_putstr_fd("\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_signal = S_SIGINT;
    }
    else if (g_signal == S_CMD)
    {
        ft_putstr_fd("\n", 1);
        rl_on_new_line();
    }
}