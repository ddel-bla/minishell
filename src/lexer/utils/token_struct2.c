#include "../../../include/minishell.h"

/*
 * Gets an element of token list by its index.
 */
t_token	*get_token_by_index(t_token *list, int index)
{
	int	i;
	t_token	*current;

	i = 0;
	current = list;
	while (current != NULL)
	{
		if (index == 1)
			return (current);
		current = current->next;
		i++;
	}
	return (NULL);
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
