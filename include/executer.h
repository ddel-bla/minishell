/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/09/01 17:44:22 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

// .......... STRUCTS ...........
typedef struct s_shell	t_shell;

typedef struct s_pid_node
{
	pid_t				pid;
	struct s_pid_node	*next;
}						t_pid_node;

// -------- REDIRECTION ---------

// ......... FUNCTIONS ..........
// ___________ command __________
void		ft_exec_proc(t_shell *shell, t_cmd *exp);

int			ft_find_path(char *exp, t_env *env, char **cmd_path);

void		ft_add_pid(t_pid_node **list, t_pid_node *pid_node);
t_pid_node	*ft_create_pid_node(pid_t pid);

void		ft_here_docs(t_shell *shell, t_redir *red);
void		ft_read_here_doc(t_shell *shell);

void		ft_handle_s_redir(t_redir *red, int pipe_fd[2], int is_last_cmd);

int			ft_is_last_cmd(t_cmd *current);

#endif
