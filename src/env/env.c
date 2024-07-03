/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:08:20 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:08:22 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Saves all the environment variables in a s_env struct.
 */
void	save_env(t_env **list, char **envp)
{
	int		i;
	int		j;
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
	int		i;
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

/*
 * Modifies an existing variable
 */
int	modify_env(t_env **list, char *name, char *value)
{
	t_env	*env;

	env = *list;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			free(env->name);
			free(env->value);
			env->name = name;
			env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

/*
 * Adds a new variable.
 */
void	add_exported_env(t_env **list, char *env)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env[i])
		if (env[i++] == '=')
			break ;
	name = ft_substr(env, 0, i - 2);
	value = ft_substr(env, i, ft_strlen(env) - 1);
	if (!env_exists(*list, name))
		add_env(list, create_env(name, value));
	else
		modify_env(list, name, value);
}
