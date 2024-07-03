/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:08 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/03 15:30:33 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expander(t_env *env, t_cmd *cmd, t_cmd **exp)
{
	int		i;
	t_cmd	*current;

	*exp = copy_cmd(cmd);
	current = *exp;
	while (current != NULL)
	{
		// input_redirection(current);
		i = -1;
		while (current->cmd[++i] != NULL)
			current->cmd[i] = expand_quotes(env, current->cmd[i]);
		current = current->next;
	}
}
