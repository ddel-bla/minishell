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
