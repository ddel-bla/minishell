/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/05 17:58:05 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "env") == 0)
			return (1);
		else if (ft_strcmp(cmd, "export") == 0)
			return (1);
		else if (ft_strcmp(cmd, "unset") == 0)
			return (1);
		else if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd, "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd, "exit") == 0)
			return (1);
		else if (ft_strcmp(cmd, "cd") == 0)
			return (1);
	}
	return (0);
}
	
void	ft_exec_proc(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (is_builtin(cmd->cmd[0]))
		exec_builtin(shell, cmd);
	else
	{
		path = ft_find_path(cmd->cmd[0], shell->env);
		if (ft_strlen(path))
			execve(path, cmd->cmd, shell->envp);
		else
			execve(cmd->cmd[0], cmd->cmd, shell->envp);
		perror("Command failed ");
		exit(127);
	}
}
