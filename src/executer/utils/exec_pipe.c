/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:29 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/03 17:25:22 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

void	ft_exec_last(t_shell *shell)
{
	int	pid;
	int	status;

	pid = ft_fork();
	if (pid == 0)
	{
		// handle_redirection(cmd->redirection);
		ft_exec_proc(shell);
	}
	else
	{
		waitpid(pid, &status, 0);
		return ;
		//if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		//{
		//	perror("Execution failed");
		//	exit(EXIT_FAILURE);
		//}
	}
}

void	ft_exec_pipe(t_shell *shell, int *fds)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		ft_exec_proc(shell);
		// handle_redirection(cmd->redirection);
	}
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		//waitpid(pid, NULL, 0);
	}
}
