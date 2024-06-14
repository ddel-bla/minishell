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
 * Returns the length of a given list.
 */
int	lst_size(t_token *list)
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
 * Returns the last element of a list
 */
t_token	*lst_last(t_token *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given list.
 */
void	add_token(t_token **list, t_token *token)
{
	if (*list == NULL)
		*list = token;
	else
		(lst_last(*list))->next = token;
}

/*
 * Prints a given list.
 */
void	print_lst(t_token *list)
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
 * Frees all the elements of a given list.
 */
void	free_lst(t_token *list)
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
 * Gets an element of a list by his index.
 */
t_token	*get_token_by_index(t_token *token_list, int index)
{
	int	current_index;
	t_token	*current;

	current_index = 0;
	current = token_list;
	
	while (current != NULL)
	{
		if (current_index == index)
			return current;
		current = current->next;
		current_index++;
	}
	return (NULL);
}
