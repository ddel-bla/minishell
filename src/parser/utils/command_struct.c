/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:23:05 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:25:42 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Creates a new commmand node.
 */
t_cmd	*create_cmd(char **arg, int operator_type, t_redir *redir)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = arg;
	cmd->operator_type = operator_type;
	cmd->redirection = redir;
	cmd->next = NULL;
	return (cmd);
}

/*
 * Returns the length of a given cmd list.
 */
int	cmd_size(t_cmd *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

/*
 * Return the last element of a cmd list.
 */
t_cmd	*cmd_last(t_cmd	*list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given cmd list.
 */
void	add_cmd(t_cmd **list, t_cmd *cmd)
{
	if (*list == NULL)
		*list = cmd;
	else
		(cmd_last(*list))->next = cmd;
}

/*
 * Frees all the elements of a given list.
 */
void	free_cmd(t_cmd *list)
{
	t_cmd	*aux;
	t_cmd	*next;
	int		i;

	aux = list;
	i = 0;
	while (aux != NULL)
	{
		next = aux->next;
		while (aux->cmd[i])
			free(aux->cmd[i++]);
		free(aux->cmd);
		free(aux);
		aux = next;
	}
}
