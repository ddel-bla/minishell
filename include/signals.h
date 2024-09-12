/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/09/12 11:36:13 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

// ......... FUNCTIONS ..........

extern int	g_signal;

void	signals_hd(void);
void	signals_execution(void);
void	signals_terminal(void);
void	signals_ignore(void);

void	sig_int_muted(int signal);
void	sig_int_active(int signal);
void	sig_quit_active(int signal);
void	sig_int_hd(int signal);

#endif
