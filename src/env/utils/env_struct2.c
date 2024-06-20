#include "../../../include/minishell.h"

/*
 * Prints a given env list.
 */
void	print_env(t_env *list)
{
	t_env	*aux;

	aux = list;
	while (aux)
	{
		printf("Enviroment variable\n");
		printf("Name:  \033[0;31m%s \033[0m\n", aux->name);
		printf("Value: \033[0;31m%s \033[0m\n", aux->value);
		aux = aux->next;
	}
}

/*
 * Gets an element of a env list by its index.
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

/*
 * Gets an element of a env list by its name.
 */
t_env	*get_env_by_name(t_env *list, char *name)
{
	t_env	*aux;

	aux = list;
	while (aux != NULL)
	{
		if (ft_strcmp(aux->name, name) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

/*
 * Deletes an element of a env list by its name.
 */
void	delete_env_by_name(t_env *list, char *name)
{
	t_env	*cur;
	t_env	*pre;

	cur = list;
	pre = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			if (pre == NULL)
				list = cur->next;
			else
				pre->next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			return ;
		}
		pre = cur;
		cur = cur->next;
	}
}
