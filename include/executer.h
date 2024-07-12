/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/12 18:56:24 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

// .......... STRUCTS ...........
typedef struct	s_shell t_shell;

typedef struct	s_pid_node
{
    pid_t		pid;
    struct	s_pid_node *next;
}				t_pid_node;

// -------- REDIRECTION ---------


// ......... FUNCTIONS ..........
// ___________ command __________
void		ft_exec_proc(t_shell *shell, t_cmd *exp);

void		ft_handle_child(int *fds, int prev_fd, t_shell *shell, t_cmd *exp);
void		ft_handle_parent(int *fds, int *prev_fd);
void		ft_handle_last(int *fds, int prev_fd, t_shell *shell, t_cmd *exp);

int			ft_find_path(char *exp, t_env *env, char **cmd_path);

void		ft_add_pid(t_pid_node **list, t_pid_node *pid_node);
t_pid_node	*ft_create_pid_node(pid_t pid);

void		handle_redir(int *fds, int *prev_fd, t_cmd *shell);
void		check_out(int *fds, int *prev_fd, t_cmd *exp);
void		check_in(int *prev_fd, t_cmd *exp);
#endif
