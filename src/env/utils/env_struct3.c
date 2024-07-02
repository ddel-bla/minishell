/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:09:48 by claferna          #+#    #+#             */
/*   Updated: 2024/07/02 18:28:41 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Sorts a given list.
 */
void	sort_env_list(t_env **list)
{
	int		swapped;
	t_env	**ptr;
	t_env	*lptr;
	t_env	*temp;

	lptr = NULL;
	swapped = 0;
	while (swapped)
	{
		swapped = 0;
		ptr = list;
		while ((*ptr)->next != lptr)
		{
			if (strcmp((*ptr)->name, (*ptr)->next->name) > 0)
			{
				temp = *ptr;
				*ptr = (*ptr)->next;
				temp->next = (*ptr)->next;
				(*ptr)->next = temp;
				swapped = 1;
			}
			ptr = &(*ptr)->next;
		}
		lptr = *ptr;
	}
}

/*
 * Returns a copy of a given list.
 */
t_env	*copy_list(t_env *list)
{
	t_env	*new_list;
	t_env	*current;
	t_env	*new_env;
	char	*value;

	new_list = NULL;
	current = list;
	while (current)
	{
		if (!current->value)
			value = "";
		else
			value = current->value;
		new_env = create_env(strdup(current->name), strdup(value));
		if (!new_env)
			return (NULL);
		add_env(&new_list, new_env);
		current = current->next;
	}
	return (new_list);
}
