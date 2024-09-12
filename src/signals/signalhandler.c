/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/09/12 16:00:31 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_signal;

void	signals_terminal(void)
{
	signal(SIGINT, sig_int_muted);
	signal(SIGQUIT, SIG_IGN);
}

// sig_int_muted hace lo mismo que active
void	signals_execution(void)
{
	signal(SIGINT, sig_int_muted);
	signal(SIGQUIT, sig_quit_active);
}

void	signals_hd(void)
{
	g_signal = 0;
	signal(SIGINT, sig_int_hd);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
