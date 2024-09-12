/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/12 19:03:20 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdio.h>

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
	{
		perror("Error stat");
		return (0);
	}
	return (S_ISDIR(statbuf.st_mode));
}

void	ft_exec_proc(t_shell *shell, t_cmd *exp)
{
	char	*path;

	if (is_builtin(exp->cmd[0]))
	{
		exec_builtin(shell, exp);
		exit(shell->exit_status);
	}
	if (exp->cmd[0] && ft_strlen(exp->cmd[0]))
	{
		if (!ft_find_path(exp->cmd[0], shell->env, &path))
			execve(path, exp->cmd, shell->envp);
		else
			execve(exp->cmd[0], exp->cmd, shell->envp);
	}
	if (is_directory(exp->cmd[0]))
	{
		perror("Is a directory");
		exit(126);
	}
	perror("Command failed");
	exit(127);
}
