/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/09/11 18:23:21 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_int_active(int signal)
{
	g_signal = signal;
	//no soy capaz de hacer que salga por aquí	
	//fprintf(stderr, "sig_int notty %i\n", g_signal);
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
	printf("aqui");
	ioctl(0,TIOCSTI, "\n");
	
	//ft_putchar_fd('\n', STDERR_FILENO);
	//close(0);
}

void	sig_quit_active(int signal)
{
	g_signal = signal;
	rl_on_new_line();
	fprintf(stderr, "Core dump\n");
}

void	sig_quit_muted(int signal)
{
	
	g_signal = signal;
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	sig_quit_null(int signal)
{
	g_signal =signal;
	printf("hola\n");
}

void	sig_int_null(int signal)
{
	g_signal = signal;
	printf("hola\n");
}
