/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:34:40 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 15:41:32 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	executer(t_cmd **cmd, t_env *env, char **envp)
{
	t_cmd	*current;
	int		status;
	pid_t	pid;

	current = *cmd;
	while (current)
	{
		if (current->operator_type == T_PIPE)
			ft_exec_pipe(current->cmd, env, envp);
		else
		{
			pid = ft_fork();
			if (pid == 0)
				ft_exec_proc(current->cmd, env, envp);
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
				{
					//TODO
					exit (EXIT_FAILURE);
				}
			}
		}
		current = current->next;
	}
}
