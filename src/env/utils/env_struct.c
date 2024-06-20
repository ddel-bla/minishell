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
t_env	*lst_last(t_env *list)
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
		(lst_last(*list))->next = env;
}

/*
 * Prints a given env list.
 */
void	print_env(t_env *list)
{
	t_env *aux;

	aux = list;
	while (aux)
	{
		printf("Enviroment variable ");
		printf("Name:  \033[0;31m%s \033[0m\n", aux->name);
		printf("Value: \033[0;31m%s \033[0m\n", aux->value);
		aux = aux->next;
	}
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
		aux = next;;
	}
}

/*
 * Gets an element of a env list by his index.
 */
t_env	*get_env_by_index(t_env *list, int index)
{
	int	i;
	t_env	*current;

	i = 0;
	current = list;
	while (current)
	{
		if (index == i)
			return (current);
		current = current->next;
		i++;
	}
	return (NULL);
}
