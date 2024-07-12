/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:17:26 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/12 19:10:58 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	check_out(int *fds, int *prev_fd, t_cmd *exp)
{
	t_redir	*act;
	int		fd;

	act = exp->redirection;
	fd = 0;
	while (act)
	{
		if (act->type == T_RED_OUT)
			fd = ft_open_out(act->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (act->type == T_RED_APP)
			fd = ft_open_out(act->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		act = act->next;
	}
	if (fds[1] == *prev_fd)
		*prev_fd = 0;
}

void	check_in(int *prev_fd, t_cmd *exp)
{
	t_redir	*act;
	int		fd;

	act = exp->redirection;
	while (act)
	{
		fprintf(stderr, "entra %i\n", act->type);
		if (act->type == T_RED_IN)
		{
			fd = ft_open_in(act->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
			*prev_fd = 0;
		}
		act = act->next;
	}
}
