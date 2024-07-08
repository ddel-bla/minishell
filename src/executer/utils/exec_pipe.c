/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:29 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/08 01:22:35 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void ft_exitstatus(t_shell *shell)
{
	t_pid_node	*current;
	t_pid_node	*temp;
	int			wstatus;

	current = shell->pid_list;
	while (current)
	{
		waitpid(current->pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			shell->exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			shell->exit_status = WTERMSIG(wstatus);
		else
			shell->exit_status = EXIT_FAILURE;
		temp = current->next;
		free(current);
		current = temp;
	}
	shell->pid_list = NULL;
}

void	handle_redirection(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == T_RED_IN)
			fd = ft_open_in(redir->file, O_RDONLY);
		else if (redir->type == T_RED_OUT)
			fd = ft_open_out(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_RED_APP)
			fd = ft_open_out(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir->type == T_RED_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

void	ft_handle_child(int *fds, int prev_fd, t_shell *shell, t_cmd *exp)
{
	close(fds[0]);
	if (prev_fd != 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	ft_exec_proc(shell, exp);
}

void	ft_handle_parent(int *fds, int *prev_fd)
{
	close(fds[1]);
	if (*prev_fd != 0)
		close(*prev_fd);
	*prev_fd = fds[0];
}

void	ft_handle_last(int *fds, int prev_fd, t_shell *shell, t_cmd *exp)
{
	pid_t	pid;

	if (is_builtin(exp->cmd[0]))
		exec_builtin(shell, exp);
	else
	{
		pid = ft_fork();
		if (pid == 0)
		{
			dup2(prev_fd, STDIN_FILENO);
			close(prev_fd);
			ft_exec_proc(shell, exp);
		}
		else
			ft_handle_parent(fds, &prev_fd);
		ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
		ft_exitstatus(shell);
	}
}
