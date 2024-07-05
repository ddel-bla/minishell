/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/05 22:40:21 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exitstatus(t_shell *shell, int pid)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		shell->exit_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		shell->exit_status = WTERMSIG(wstatus);
	else
		shell->exit_status = EXIT_FAILURE;
}

void	executer(t_shell *shell)
{
	t_cmd	*current;
	int		fds[2];
	int		prev_fd;
	int		pid;

	current = shell->exp;
	prev_fd = 0;
	while (current->next)
	{
		if (is_builtin(current->cmd[0]))
			exec_builtin(shell, current);
		else
		{
			ft_pipe(fds);
			pid = ft_fork();
			if (pid == 0)
				ft_handle_child(fds, prev_fd, shell, current);
			else
				ft_handle_parent(fds, &prev_fd);
			current = current->next;
		}
	}
		if (is_builtin(current->cmd[0]))
			exec_builtin(shell, current);
		{
			pid = ft_fork();
		if (pid == 0)
			ft_handle_last(prev_fd, shell, current);
		else
			ft_handle_parent(fds, &prev_fd);
		ft_exitstatus(shell, pid);
	}
}
