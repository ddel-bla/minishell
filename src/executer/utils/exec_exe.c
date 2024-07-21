/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/16 21:09:43 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exec_proc(t_shell *shell, t_cmd *exp)
{
	char	*path;

	if (is_builtin(exp->cmd[0]))
	{
		exec_builtin(shell, exp);
		exit(shell->exit_status);
	}
	if (exp->cmd[0])
	{
		if (!ft_find_path(exp->cmd[0], shell->env, &path))
			execve(path, exp->cmd, shell->envp);
		else
			execve(exp->cmd[0], exp->cmd, shell->envp);
		perror("Command failed");
	}
	exit(127);
}
