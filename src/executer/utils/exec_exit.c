/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/15 09:34:37 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	update_exit_status(t_shell *shell, int wstatus)
{
	if (WIFSIGNALED(wstatus))
	{
		shell->exit_status = 128 + WTERMSIG(wstatus);
		if (WTERMSIG(wstatus) == SIGQUIT)
			fprintf(stderr, "Core dump\n");
		else if (WTERMSIG(wstatus) == SIGINT)
			fprintf(stderr, "\n");
	}
	else if (WIFEXITED(wstatus))
		shell->exit_status = WEXITSTATUS(wstatus);
	else
		shell->exit_status = EXIT_FAILURE;
}

static void	free_pid_list(t_pid_node **pid_list)
{
	t_pid_node	*current;
	t_pid_node	*temp;

	current = *pid_list;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	*pid_list = NULL;
}

void	ft_exitstatus(t_shell *shell)
{
	int			wstatus;
	t_pid_node	*current;

	current = shell->pid_list;
	while (current)
	{
		waitpid(current->pid, &wstatus, 0);
		if (!current->next)
			update_exit_status(shell, wstatus);
		current = current->next;
	}
	free_pid_list(&shell->pid_list);
}
