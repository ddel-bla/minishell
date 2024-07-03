/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/04 00:50:13 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executer(t_shell *shell)
{
	t_cmd	*current;
	int		fds[2];

	current = shell->cmd;
	while (current)
	{
		if (current->next && current->operator_type == T_PIPE)
		{
			fprintf(stderr, "Debug:  %d\n", 1);
			ft_pipe(fds);
			ft_exec_pipe(shell, current, fds);
		}
		else
		{
			fprintf(stderr, "Debug:  %d\n", 2);
			ft_exec_last(shell, current);
		}
		current = current->next;
	}
}
