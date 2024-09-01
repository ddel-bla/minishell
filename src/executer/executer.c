/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/01 17:42:05 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_exitstatus(t_shell *shell)
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

static void	ft_set_input_child(int prev_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

static void	ft_set_input_parent(int prev_fd, int pipe_fds[2], t_cmd *current)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (ft_is_last_cmd(current))
	{
		close(pipe_fds[1]);
		prev_fd = pipe_fds[0];
	}
}

void	ft_exec(t_shell *shell, int prev_fd, int pipe_fds[2])
{
	t_cmd	*c;
	pid_t	pid;

	c = shell->exp;
	ft_read_here_doc(shell);
	while (c)
	{
		if (!ft_is_last_cmd(c))
			ft_pipe(pipe_fds);
		pid = ft_fork();
		if (pid == 0)
		{
			ft_set_input_child(prev_fd);
			ft_handle_s_redir(c->redirection, pipe_fds, ft_is_last_cmd(c));
			ft_exec_proc(shell, c);
		}
		else
		{
			ft_set_input_parent(prev_fd, pipe_fds, c);
			ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
		}
		c = c->next;
	}
}

void	executer(t_shell *shell)
{
	int		prev_fd;
	int		pipe_fds[2];

	prev_fd = -1;
	if (shell->n_cmds == 1 && is_builtin(shell->exp->cmd[0]))
		exec_builtin(shell, shell->exp);
	else
		ft_exec(shell, prev_fd, pipe_fds);
	ft_exitstatus(shell);
}
