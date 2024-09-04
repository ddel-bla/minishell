/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:05:21 by claferna          #+#    #+#             */
/*   Updated: 2024/07/23 19:52:56 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	valid_flag(char *flag);

void	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->cmd[i] && valid_flag(cmd->cmd[i]))
		i++;
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i++], 1);
		if (cmd->cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if ((cmd->cmd[1] && !valid_flag(cmd->cmd[1])) \
			|| count_args(cmd) == 1)
		ft_putchar_fd('\n', 1);
	shell->exit_status = 0;
}
/*
static int	valid_flag(char *flag)
{
	int	i;

	if (ft_strcmp(flag, "-n") == 0)
		return (1);
	else if (ft_strncmp(flag, "-n", 2) == 0)
	{
		i = 2;
		while (flag[i])
			if (flag[i++] != 'n')
				return (0);
		return (1);
	}
	return (0);
}
*/

static int	valid_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] == '-')
	{
		while (flag[++i] != 0 && flag[i])
			if (flag[i] != 'n')
				return (0);
		return (1);
	}
	else
		return (0);
}
