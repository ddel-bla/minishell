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

// ......... FUNCTIONS ..........
void	signal_init(void);
void	handle_ctrl_d(char *input);
void	restore_signals(void);
void	ignore_signals(void);
void	signal_init(void);
void	treat_parent_signals(int wstatus, int pid);
void	ft_sigemptyset(sigset_t *set);
void	ft_process_here_doc(t_shell *shell, t_redir *red, \
		struct sigaction *sa_old);
void	ft_here_docs_handle_signal(struct sigaction *sa_old, \
		struct sigaction *sa_new);
void	heredoc_sigint_handler(int signal);

#endif
