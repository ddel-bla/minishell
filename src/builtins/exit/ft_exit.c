/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:06:22 by claferna          #+#    #+#             */
/*   Updated: 2024/09/15 17:01:30 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	validate_exit(t_cmd *cmd);
static int	check_number(char *cmd);

/*
 * Replicates the behaviour of the exit command.
 */
void	ft_exit(t_shell *shell, t_cmd	*cmd)
{
	if (!validate_exit(cmd))
	{
		if (cmd->cmd[1])
			shell->exit_status = ft_atoi(cmd->cmd[1]);
		exit(shell->exit_status);
	}
}

/*
 * Validates the input of the exit command.
 */
static int	validate_exit(t_cmd *cmd)
{
	if (count_args(cmd) > 2)
	{
		print_error("exit: too many arguments");
		return (1);
	}
	if (count_args(cmd) == 1)
		return (0);
	if (cmd->cmd[1] && !check_number(cmd->cmd[1]))
		return (0);
	return (0);
}

/*
 * Checks if the argument is a valid number (including sign)
 */
static int	check_number(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	if (!cmd[i])
	{
		ft_putstr_fd("exit: a numeric argument", 2);
		ft_putendl_fd("is required", 2);
		return (0);
	}
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
		{
			ft_putstr_fd("exit: a numeric argument", 2);
			ft_putendl_fd("is required", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
