/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:53:10 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/08 01:06:34 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_add_pid(t_pid_node **list, t_pid_node *pid_node)
{
	if (*list == NULL)
		*list = pid_node;
    else if ((*list)->next == NULL)
		(*list)->next = pid_node;
	else
		ft_add_pid(&(*list)->next, pid_node);
}

t_pid_node	*ft_create_pid_node(pid_t pid)
{
	t_pid_node	*new_node;
	
	new_node = (t_pid_node *)malloc(sizeof(t_pid_node));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}
