/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/09/12 15:31:42 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//creo que no hace falta
void	sig_int_active(int signal)
{
	g_signal = signal;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
}

void	sig_int_muted(int signal)
{
	g_signal = signal;
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_int_hd(int signal)
{
	g_signal = signal;
	ioctl(0, TIOCSTI, "\n");
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	sig_quit_active(int signal)
{
	g_signal = signal;
	rl_on_new_line();
}

void	sig_quit_muted(int signal)
{
	g_signal = signal;
	rl_replace_line("", 0);
	rl_on_new_line();
}
