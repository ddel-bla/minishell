/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:53:38 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 12:36:37 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	input_redirection(t_cmd *cmd)
{
	int		fd;

	fd = 0;
	while (cmd->redirection != NULL)
	{
		if (cmd->redirection->type == T_RED_IN)
			red_in(fd, cmd->redirection->file);
//		else if (cmd->redirection->type == T_RED_HER)
//			red_her(fd, cmd->redirection->file);
//		else if (cmd->redirection->type == T_RED_HER)
//			red_out(fd, cmd->redirection->file);
//		else if (cmd->redirection->type == T_RED_HER)
//			red_app(fd, cmd->redirection->file);
		cmd->redirection = cmd->redirection->next;
	}
}
