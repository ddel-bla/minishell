/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/12 19:47:59 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

inline int	ft_is_last_cmd(t_cmd *current)
{
	return (current->next == NULL);
}

pid_t	aux_ft_exec(int pipe_fds[2], t_cmd *cmd)
{
	pid_t	pid;

	if (!ft_is_last_cmd(cmd))
		ft_pipe(pipe_fds);
	pid = ft_fork();
	return (pid);
}

void	shell_cleanup_here_docs(t_shell *shell)
{
	t_cmd	*current;
	t_redir	*red;

	current = shell->exp;
	while (current != NULL)
	{
		red = current->redirection;
		while (red != NULL)
		{
			if (red->heredoc_file)
			{
				unlink(red->heredoc_file);
				free(red->heredoc_file);
				red->heredoc_file = NULL;
			}
			red = red->next;
		}
		current = current->next;
	}
}
