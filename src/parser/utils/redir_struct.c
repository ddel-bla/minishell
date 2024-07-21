/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:54 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:34:02 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Creates a new redir node
 */
t_redir	*create_redir(int type, char *file)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

/*
 * Returns the length of a given redir list.
 */
int	redirs_size(t_redir *list)
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
 * Returns the last element of a redir list
 */
t_redir	*lst_last(t_redir *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given redir list.
 */
void	add_redir(t_redir **list, t_redir *redir)
{
	if (*list == NULL)
		*list = redir;
	else
		(lst_last(*list))->next = redir;
}

/*
 * Frees all the elements of a given cmd list.
 */
void	free_redirs(t_redir *list)
{
	t_redir	*aux;

	while (list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux->file);
		free(aux);
	}
}
