/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/02 12:35:45 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// .......... STRUCTS ...........
// -------- REDIRECTION ---------


// ......... FUNCTIONS ..........
// ___________ command __________
t_cmd	*copy_cmd(t_cmd *original);
char	*expand_quotes(t_env *list, char *cmd);
void	input_redirection(t_cmd *cmd);


void	red_in(int fd, char *file);
void	red_her(int fds[2], char *limiter);

#endif
