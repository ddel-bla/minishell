/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:58:28 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 15:58:29 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Checks whether the executed command is one of the built-ins
 * methods and executes it.
 */
void	exec_builtin(t_shell *shell, t_cmd *cmd)
{
	if (cmd->cmd[0])
	{
		if (ft_strcmp(cmd->cmd[0], "env") == 0)
			ft_env(shell, cmd);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
			ft_export(shell, cmd);
		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
			ft_unset(shell, cmd);
		else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
			ft_pwd(shell, cmd);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			ft_echo(shell, cmd);
		else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
			ft_exit(shell, cmd);
		else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
			ft_cd(shell, cmd);
	}
}
