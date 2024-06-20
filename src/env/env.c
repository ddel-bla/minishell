#include "../../include/minishell.h"

/*
 * Saves all the environment variables in a s_env struct.
 */
void	save_env(t_env **list, char **envp)
{
	int	i;
	int	j;
	char	*env;
	char	*name;
	char	*value;

	i = 0;
	while (envp[i])
	{
		env = strdup(envp[i]);
		j = 0;
		while (env[j])
			if (env[j++] == '=')
				break ;	
		name = ft_substr(env, 0, j - 2);
		value = ft_substr(env, j, ft_strlen(env) - 1);
		add_env(list, create_env(name, value));
		free(env);
		i++;
	}
}

/*
 * Converts a list of env back to a char **.
 */
char	**env_list_to_char(t_env **list)
{
	int	i;
	char	**array;
	t_env	*env;
	char	*aux;
       
	env = *list;
	array = (char **)malloc(sizeof(char *) * (env_size(*list) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		aux = ft_strjoin(env->name, "=");
		if (env->value == NULL)
			array[i] = aux;
		else
		{
			array[i] = ft_strjoin(aux, env->value);
			free(aux);
		}
		env = env->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
