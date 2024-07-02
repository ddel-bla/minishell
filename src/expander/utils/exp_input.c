/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:37:10 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 12:31:44 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	red_in(int fd, char *file)
{
	fd = ft_open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	red_her(int fds[2], char *limiter)
{
	char	*line;
	char	*check;

	check = ft_strjoin(limiter, "\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!ft_strncmp(line, check, ft_strlen(line)) && line)
			break ;
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(check);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}
