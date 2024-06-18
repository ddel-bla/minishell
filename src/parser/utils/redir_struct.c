/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:54 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:28:39 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Creates a new redir node
 */
t_redir	*create_redir(int type, char *file)
{
	t_redir	*red;

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
 * Prints a given cmd list.
 */
void	print_redirs(t_redir *list)
{
	t_redir	*aux;

	aux = list;
	while (aux != NULL)
	{
		printf("Redirection ");
		printf("type: \033[0;31m%s \033[0m", get_str_types(aux->type));
		printf("file: \033[0;35m%s \033[0m\n", aux->file);
		aux = aux->next;
	}
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
		free(aux);
	}
}

/*
 * Gets an element of a redir list by his index.
 */
t_redir	*get_redir_by_index(t_redir *list, int index)
{
	int		i;
	t_redir	*current;

	i = 0;
	current = list;
	while (current != NULL)
	{
		if (index == i)
			return (current);
		current = current->next;
		i++;
	}
	return (NULL);
}
