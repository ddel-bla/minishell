/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/03 13:28:55 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

// .......... STRUCTS ...........
// .......... STRUCTS ...........
typedef struct s_shell t_shell;
// -------- REDIRECTION ---------


// ......... FUNCTIONS ..........
// ___________ command __________
void	ft_exec_proc(t_shell *shell);
void	ft_exec_last(t_shell *shell);
void	ft_exec_pipe(t_shell *shell, int *fds);
char	*ft_find_path(char *cmd, t_env *env);

#endif
