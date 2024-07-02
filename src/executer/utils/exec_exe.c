/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 15:42:23 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exec_proc(char **cmd, t_env *env, char **envp)
{
	char	*path;

	path = ft_find_path(cmd[0], env);
	if (ft_strlen(path))
		execve(path, cmd, envp);
	else
		execve(cmd[0], cmd, envp);
	perror("Command failed ");
	exit(127);
}
