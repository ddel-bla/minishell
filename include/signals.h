/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/07/19 09:52:02 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define S_INIT         20  // Signal init
# define S_HEREDOC      21  // Signal heredoc
# define S_HEREDOC_END  22  // Signal end heredoc
# define S_CMD          23  // Signal cmd
# define S_HEREDOC_MID  24  // Signal middle heredoc

// ......... FUNCTIONS ..........
void	signal_init(void);
void	handle_ctrl_d(char *input);
void	restore_signals(void);
void	ignore_signals(void);
void	signal_init(void);
void	treat_parent_signals(int wstatus, int pid);
void	ft_sigemptyset(sigset_t *set);

#endif