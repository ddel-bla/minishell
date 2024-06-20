#include "../../include/minishell.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
char    *ft_substr(char *str, int start, int end)
{
        int     len;
        int     i;
        char    *aux;

        if (start > end || start < 0 || end >= ft_strlen(str))
                return (NULL);
        len = end - start + 1;
        aux = (char *)malloc(sizeof(char) * len + 1);
        if (!aux)
                return (NULL);
        i = 0;
        while (start <= end)
                aux[i++] = str[start++];
        aux[i] = '\0';
        return (aux);
}

/*
 * Initializes all the environment variables
 */
void	initialize_env(char **envp, t_env **env_list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		char *env = strdup(envp[i]);
		int j = 0;
		while (env[j])
		{
			if (env[j] == '=')
				break;	
			j++;
		}
		char *name = ft_substr(env, 0, j-1);
		char *value = ft_substr(env, j + 1, ft_strlen(env) -1);
	        add_env(env_list, create_env(name, value));
		i++;
		free(env);
	}
}

/*
 * Converts a list of env back to a char **.
 */
char	**env_list_to_char(t_env **list)
{
	int	len;
	int	i;
	char	**array;
	t_env	*aux;
       
	aux = *list;
	len = env_size(*list);
	array = (char **)malloc(sizeof(char *) * (len + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (aux)
	{
		int len1 = ft_strlen(aux->name);
		int len2 = 0;
		if (aux->value != NULL)
			len2 = ft_strlen(aux->value);
		len = len1 + len2 + 2;
		array[i] = (char *)malloc(sizeof(char) * (len));
        	if (!array[i])
			return (NULL);
		snprintf(array[i], len, "%s=%s", aux->name, aux->value);
		aux = aux->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

int main(int argc, char **argv, char **envp)
{
	t_env	*list_env = NULL;
	initialize_env(envp, &list_env);	
	char **e = env_list_to_char(&list_env);
	//print_env(list_env);
	int i = 0;
	while (e[i])
		printf("%s\n", e[i++]);
	free_env(list_env);
}
