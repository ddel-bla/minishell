/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:18:10 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/05 20:13:09 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	ft_open_in(char *file, int mode)
{
	int	fd;

	fd = open(file, mode);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	ft_open_out(char *file, int mode, int flag)
{
	int	fd;

	fd = open(file, mode, flag);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_pipe(int *fds)
{
	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "env") == 0)
			return (1);
		else if (ft_strcmp(cmd, "export") == 0)
			return (1);
		else if (ft_strcmp(cmd, "unset") == 0)
			return (1);
		else if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd, "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd, "exit") == 0)
			return (1);
		else if (ft_strcmp(cmd, "cd") == 0)
			return (1);
	}
	return (0);
}
