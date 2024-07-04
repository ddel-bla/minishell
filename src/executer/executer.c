/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/04 17:15:06 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executer(t_shell *shell)
{
	t_cmd	*current;
	int		fds[2];
	int		prev_fd;
	int		pid;

	current = shell->cmd;
	prev_fd = 0;
	while (current->next)
	{
		ft_pipe(fds);
		pid = ft_fork();
		if (pid == 0)
			ft_handle_child(fds, prev_fd, shell, current);
		else
			ft_handle_parent(fds, &prev_fd);
		current = current->next;
	}
	pid = ft_fork();
	if (pid == 0)
		ft_handle_last(prev_fd, shell, current);
	else
		waitpid(pid, NULL, 0);
}
