/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/16 21:08:20 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executer(t_shell *shell)
{
	t_cmd	*current;
	int		fds[2];
	int		prev_fd;
	pid_t	pid;

	current = shell->exp;
	prev_fd = 0;
	if (current->next == NULL && is_builtin(current->cmd[0]))
		exec_builtin(shell, current);
	else
	{
		g_signal = S_CMD;
		while (current->next)
		{
			ft_pipe(fds);
			pid = ft_fork();
			if (pid == 0)
				ft_handle_child(fds, prev_fd, shell, current);
			else
				ft_handle_parent(fds, &prev_fd);
			ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
			current = current->next;
		}
		ft_handle_last(fds, prev_fd, shell, current);
	}
}
