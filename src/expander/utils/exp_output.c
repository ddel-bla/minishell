/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:37:10 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 12:28:18 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_out_process(char *outfile, char *cmd, char **envp, int mode)
{
	int		fd;
	int		pid;

	pid = ft_fork();
	if (pid == 0)
	{
		if (mode)
			fd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_exec_proc(cmd, envp);
	}
	return (pid);
}
