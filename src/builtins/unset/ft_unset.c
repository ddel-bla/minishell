/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:07:23 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:31:03 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Deletes an environment variable.
 */
void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	char	*arg;
	int		i;

	i = 1;
	while (cmd->cmd[i])
	{
		arg = cmd->cmd[i];
		delete_env_by_name(shell->env, arg);
		i++;
	}
	shell->exit_status = 0;
}
