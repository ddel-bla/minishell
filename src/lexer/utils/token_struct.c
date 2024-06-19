/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:17:35 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:19:17 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Creates a new token node
 */
t_token	*create_token(char *value, int type, int index)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->index = index;
	token->next = NULL;
	return (token);
}

/*
 * Returns the length of a given token list.
 */
int	tokens_size(t_token *list)
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
 * Returns the last element of a token list
 */
t_token	*token_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given token list.
 */
void	add_token(t_token **list, t_token *token)
{
	if (*list == NULL)
		*list = token;
	else
		(token_last(*list))->next = token;
}

/*
 * Frees all the elements of a given token list.
 */
void	free_tokens(t_token *list)
{
	t_token	*aux;
	t_token	*next;

	aux = list;
	while (aux != NULL)
	{
		next = aux->next;
		free(aux->value);
		free(aux);
		aux = next;
	}
}
