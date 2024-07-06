/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:38:59 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/06 17:09:30 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_exec_proc(t_shell *shell, t_cmd *exp)
{
	char	*path;

	if (!ft_find_path(exp->cmd[0], shell->env, &path))
		execve(path, exp->cmd, shell->envp);
	else
		execve(exp->cmd[0], exp->cmd, shell->envp);
	perror("Command failed ");
	exit(127);
}
