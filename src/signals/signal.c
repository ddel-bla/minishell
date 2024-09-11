/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/09/11 16:19:38 by ddel-bla         ###   ########.fr       */
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
	//rl_redisplay();
	//fprintf(stderr, "sig_int tty %i\n", g_signal);	
	//se comporta bien pero falta salir con $? 130
}

void	sig_int_hd(int signal)
{
	g_signal = signal;
	//close(0);
	//return ;
}

void	sig_quit_active(int signal)
{
	g_signal = signal;
	rl_on_new_line();
	fprintf(stderr, "Core dump\n");
	//rl_redisplay();
	//fprintf(stderr, "sigquit tty %i\n", g_signal);
	//se comporta bien pero falta salir con $? 131
}


void	sig_quit_muted(int signal)
{
	g_signal = signal;
	//no soy capaz de hacer que salga por aquí	
	//fprintf(stderr, "sigquit notty %i\n", g_signal);
}
		