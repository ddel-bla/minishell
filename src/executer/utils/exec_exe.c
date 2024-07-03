/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/04 00:41:36 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exec_proc(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	// TODO include Builtins
	path = ft_find_path(cmd->cmd[0], shell->env);
	if (ft_strlen(path))
		execve(path, cmd->cmd, shell->envp);
	else
		execve(cmd->cmd[0], shell->cmd->cmd, shell->envp);
	perror("Command failed ");
	exit(127);
}
