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

void	treat_parent_signals(int wstatus, int pid)
{
	ignore_signals();
	waitpid(pid, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGINT)
			ft_putstr_fd("\n", 1);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
	}
	signal_init();
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_sigemptyset(sigset_t *set)
{
	if (set == NULL)
		return ;
	ft_memset(set, 0, sizeof(sigset_t));
}
