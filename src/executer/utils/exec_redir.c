/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:17:26 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/23 19:20:54 by ddel-bla         ###   ########.fr       */
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

static void	red_her(void *shell, char *limiter, int mode, int *fds)
{
	char	*line;

	g_signal = S_HEREDOC;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || (!ft_strncmp(line, limiter, ft_strlen(line))))
			break ;
		if (line)
			add_history(line);
		if (mode)
			line = here_expand(line, shell);
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
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
			red_her(shell, act->file, 0, fds);
		else if (act->type == T_RED_HER_EX)
			red_her(shell, act->file, 0, fds);
		act = act->next;
	}
}
