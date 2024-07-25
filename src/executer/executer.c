/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/25 21:42:25 by ddel-bla         ###   ########.fr       */
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

int	ft_count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	ft_handle_single(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
		ft_exec_proc(shell, cmd);
	else
		ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
}

void	executer(t_shell *shell)
{
	t_cmd	*current;
	int		pipe_count;
	int		**pipes;
	int		i;

	pipe_count = ft_count_commands(shell->exp);
	if (pipe_count == 1)
	{
		if (is_builtin(shell->exp->cmd[0]))
			exec_builtin(shell, shell->exp);
		else
			ft_handle_single(shell, shell->exp);
	}
	else
	{
		pipes = (int **)ft_malloc(pipe_count * sizeof(int *));
		ft_create_pipes(pipe_count, pipes);
		current = shell->exp;
		ft_handle_first(pipes, shell, current);
		current = current->next;
		i = 1;
		while (current->next)
		{
			ft_handle_middle(pipes, i, shell, current);
			current = current->next;
			i++;
		}
		ft_handle_last(pipes, i, shell, current);
		ft_close_pipes(pipe_count, pipes);
	}
	ft_exitstatus(shell);
}
