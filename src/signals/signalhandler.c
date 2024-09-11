/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/09/11 18:09:52 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_signal;

void	signals_terminal(void)
{
	signal(SIGINT, sig_int_muted);
	signal(SIGQUIT, sig_quit_muted);
}

void	signals_execution(void)
{
	signal(SIGINT, sig_int_active);
	signal(SIGQUIT, sig_quit_active);
}

void	signals_hd(void)
{
	//signal(SIGINT, sig_int_active);
	signal(SIGINT, sig_int_hd);
	signal(SIGQUIT, sig_quit_muted);
}
void	signals_notty(void)
{
	signal(SIGINT, sig_int_null);
	signal(SIGQUIT, sig_quit_null);
}
