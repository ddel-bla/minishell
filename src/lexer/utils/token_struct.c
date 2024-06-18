#include "../../../include/minishell.h"

/*
 * Creates a new token node
 */
t_token	*create_token(char *value, int type, int index)
{
	t_token *token;

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
 * Prints a given token list.
 */
void	print_tokens(t_token *list)
{
	t_token	*aux;

	aux = list;
	while (aux != NULL)
	{
		printf("%d token = ", aux->index + 1);
		printf("value:\033[0;31m %s \033[0m", aux->value);
                printf("type:\033[0;35m %s \033[0m\n", get_str_types(aux->type));
		aux = aux->next;
	}
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

/*
 * Gets an element of a token list by his index.
 */
t_token	*get_token_by_index(t_token *list, int index)
{
	int	i;
	t_token	*current;

	i = 0;
	current = list;
	while (current != NULL)
	{
		if (index == i)
			return current;
		current = current->next;
		i++;
	}
	return (NULL);
}
