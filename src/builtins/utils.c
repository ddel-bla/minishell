/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:58:35 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 15:58:37 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Counts the number of arguments a command has
 */
int	count_args(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	return (i);
}
