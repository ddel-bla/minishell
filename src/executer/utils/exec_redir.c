/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:29 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/01 17:53:23 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	handle_heredoc_redirection(t_redir *red)
{
	int	fd;

	fd = ft_open(red->heredoc_file, O_RDONLY, 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_input_redirection(t_redir *red)
{
	int	fd;

	fd = ft_open(red->file, O_RDONLY, 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_append_redirection(t_redir *red, int *out_redirected)
{
	int	fd;

	fd = ft_open(red->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*out_redirected = 1;
}

static void	handle_output_redirection(t_redir *red, int *out_redirected)
{
	int	fd;

	fd = ft_open(red->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*out_redirected = 1;
}

void	ft_handle_s_redir(t_redir *red, int pipe_fd[2], int is_last_cmd)
{
	int	out_redirected;

	out_redirected = 0;
	while (red != NULL)
	{
		if (red->type == T_RED_HER || red->type == T_RED_HER_EX)
			handle_heredoc_redirection(red);
		else if (red->type == T_RED_IN)
			handle_input_redirection(red);
		else if (red->type == T_RED_APP)
			handle_append_redirection(red, &out_redirected);
		else if (red->type == T_RED_OUT)
			handle_output_redirection(red, &out_redirected);
		red = red->next;
	}
	if (!out_redirected && !is_last_cmd)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else if (!is_last_cmd)
		close(pipe_fd[1]);
}
