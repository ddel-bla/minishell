#include "../../../include/minishell.h"

/*
 * Prints all the environment variables.
 */
void	ft_env(t_env	*env)
{
	t_env	*aux;
	char	*value;

	aux = env;
	while (aux)
	{
		if (aux->value == NULL)
			value = "";
		else
			value = aux->value;
		printf("%s=%s\n", aux->name, value);
		aux = aux->next;
	}
}
