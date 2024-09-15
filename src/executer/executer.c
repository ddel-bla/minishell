/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/15 09:34:50 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_set_input_child(int prev_fd, int pipe_fds[2], int is_last_cmd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!is_last_cmd)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
}

static void	ft_set_input_parent(int *prev_fd, int pipe_fds[2], t_cmd *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (!ft_is_last_cmd(current))
	{
		*prev_fd = pipe_fds[0];
		close(pipe_fds[1]);
	}
}

void	ft_exec(t_shell *shell, int prev_fd, int pipe_fds[2])
{
	t_cmd	*c;
	pid_t	pid;

	c = shell->exp;
	while (c)
	{
		pid = aux_ft_exec(pipe_fds, c);
		if (pid == 0)
		{
			signals_execution();
			ft_set_input_child(prev_fd, pipe_fds, ft_is_last_cmd(c));
			ft_handle_s_redir(c->redirection, pipe_fds, ft_is_last_cmd(c));
			ft_exec_proc(shell, c);
		}
		else
		{
			ft_set_input_parent(&prev_fd, pipe_fds, c);
			ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
		}
		c = c->next;
	}
}

static void	ft_fds_redir_builtin(t_shell *shell, t_cmd *exp)
{
	int	ini_stdin;
	int	ini_stdout;

	ini_stdin = dup(STDIN_FILENO);
	ini_stdout = dup(STDOUT_FILENO);
	ft_handle_s_redir(exp->redirection, NULL, 1);
	exec_builtin(shell, shell->exp);
	dup2(ini_stdin, STDIN_FILENO);
	dup2(ini_stdout, STDOUT_FILENO);
	close(ini_stdin);
	close(ini_stdout);
}

void	executer(t_shell *shell)
{
	int		prev_fd;
	int		pipe_fds[2];

	prev_fd = -1;
	g_signal = 0;
	signals_hd();
	ft_read_here_doc(shell);
	if (g_signal == SIGINT)
		return ;
	signals_ignore();
	if (shell->n_cmds == 1 && is_builtin(shell->exp->cmd[0]))
		ft_fds_redir_builtin(shell, shell->exp);
	else
		ft_exec(shell, prev_fd, pipe_fds);
	ft_exitstatus(shell);
}
