/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:05:51 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:05:52 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Prints all the environment variables.
 */
void	ft_env(t_shell	*shell, t_cmd *cmd)
{
	t_env	*env;
	char	*value;

	env = shell->env;
	if (count_args(cmd) > 1)
	{
		ft_putstr_fd("\033[1;31mnv: <", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putendl_fd(">: No such file or directory\033[0m", 2);
		shell->exit_status = 127;
		return ;
	}
	while (env)
	{
		if (env->value == NULL)
			value = "";
		else
			value = env->value;
		printf("%s=%s\n", env->name, value);
		env = env->next;
	}
}
