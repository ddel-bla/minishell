/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:07:07 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:07:08 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Reproduces the behaviour of the 'pwd' command.
 */
void	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	shell->exit_status = 0;
}
