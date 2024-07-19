/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:17:26 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/17 11:52:13 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	check_out(int *fds, int *prev_fd, t_cmd *exp)
{
	t_redir	*act;
	int		fd;

	act = exp->redirection;
	while (act)
	{
		if (act->type == T_RED_OUT)
		{
			fd = ft_open(act->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (act->type == T_RED_APP)
		{
			fd = ft_open(act->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		act = act->next;
	}
	if (fds[1] == *prev_fd)
		*prev_fd = 0;
}

static void	red_her(t_shell *shell, char *limiter, int mode, int fd)
{
	char	*line;

	g_signal = S_HEREDOC;
	while (1)
	{	
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || (!ft_strncmp(line, limiter, ft_strlen(line))))
			break ;
		if (mode)
			line = here_expand(line, shell);
		write(fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	dup2(fd, STDIN_FILENO);
	g_signal = S_HEREDOC_END;
}

void	check_in(t_shell *shell, int *prev_fd, int *fds, t_cmd *exp)
{
	t_redir	*act;
	int		fd;

	act = exp->redirection;
	while (act)
	{
		if (act->type == T_RED_IN)
		{
			fd = ft_open(act->file, O_RDONLY, 0664);
			if (*prev_fd != 0)
				close(*prev_fd);
			dup2(fd, STDIN_FILENO);
			close(fd);
			*prev_fd = 0;
		}
		else if (act->type == T_RED_HER)
			red_her(shell, act->file, 0, fds[1]);
		else if (act->type == T_RED_HER_EX)
			red_her(shell, act->file, 0, fds[1]);
		act = act->next;
	}
}
