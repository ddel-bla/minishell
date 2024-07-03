/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/03 14:16:16 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exec_proc(t_shell *shell)
{
	char	*path;

	// TODO include Builtins
	path = ft_find_path(shell->cmd->cmd[0], shell->env);
	if (ft_strlen(path))
		execve(path, shell->cmd->cmd, shell->envp);
	else
		execve(shell->cmd->cmd[0], shell->cmd->cmd, shell->envp);
	perror("Command failed ");
	exit(127);
}
