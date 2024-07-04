/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/04 16:59:20 by ddel-bla         ###   ########.fr       */
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
void	ft_handle_child(int *fds, int prev_fd, t_shell *shell, t_cmd *cmd);
void	ft_handle_parent(int *fds, int *prev_fd);
void	ft_handle_last(int prev_fd, t_shell *shell, t_cmd *cmd);
char	*ft_find_path(char *cmd, t_env *env);
#endif
