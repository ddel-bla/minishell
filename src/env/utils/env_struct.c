/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:08:40 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:08:41 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Create a new env node.
 */
t_env	*create_env(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

/*
 * Returns the length of a given env list.
 */
int	env_size(t_env *list)
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
 * Returns the last element of a env list
 */
t_env	*env_last(t_env *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given env list.
 */
void	add_env(t_env **list, t_env *env)
{
	if (*list == NULL)
		*list = env;
	else
		(env_last(*list))->next = env;
}

/*
 * Frees all the elements of a given env list.
 */
void	free_env(t_env *list)
{
	t_env	*aux;
	t_env	*next;

	aux = list;
	while (aux)
	{
		next = aux->next;
		free(aux->name);
		free(aux->value);
		free(aux);
		aux = next;
	}
}
