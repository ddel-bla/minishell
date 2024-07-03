/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/04 00:41:15 by ddel-bla         ###   ########.fr       */
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
void	ft_exec_proc(t_shell *shell, t_cmd *cmd);
void	ft_exec_last(t_shell *shell, t_cmd *cmd);
void	ft_exec_pipe(t_shell *shell, t_cmd *cmd, int *fds);
char	*ft_find_path(char *cmd, t_env *env);

#endif
