/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:29 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/25 21:21:38 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_create_pipes(int pipe_count, int **pipes)
{
	int	i;

	i = 0;
	while (i < pipe_count - 1)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_close_pipes(int pipe_count, int **pipes)
{
	int	i;

	i = 0;
	while (i < pipe_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	ft_handle_first(int **pipes, t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(pipes[0][0]);
		dup2(pipes[0][1], STDOUT_FILENO);
		close(pipes[0][1]);
		ft_exec_proc(shell, cmd);
	}
	else
	{
		close(pipes[0][1]);
		ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
	}
}

void	ft_handle_middle(int **pipes, int i, t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
		ft_exec_proc(shell, cmd);
	}
	else
	{
		close(pipes[i][1]);
		close(pipes[i - 1][0]);
		ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
	}
}

void	ft_handle_last(int **pipes, int i, t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		ft_exec_proc(shell, cmd);
	}
	else
	{
		close(pipes[i - 1][0]);
		ft_add_pid(&shell->pid_list, ft_create_pid_node(pid));
	}
}
