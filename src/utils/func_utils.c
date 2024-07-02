/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:18:10 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 16:22:58 by ddel-bla         ###   ########.fr       */
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
int	ft_open(char *file, int mode)
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

void	ft_pipe(int *fds)
{
	if (pipe(fds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
