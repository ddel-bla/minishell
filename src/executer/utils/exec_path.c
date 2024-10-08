/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:01:23 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/23 19:20:20 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_free_it(char **tab, char *sub)
{
	int	i;

	i = 0;
	free(sub);
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static char	**ft_get_path(t_env *env)
{
	char	**tab;
	t_env	*myenv;

	myenv = get_env_by_name(env, "PATH");
	if (!myenv || !myenv->value)
		return (NULL);
	tab = ft_split(myenv->value, ':');
	return (tab);
}

int	ft_find_path(char *cmd, t_env *env, char **cmd_path)
{
	char	**paths;
	char	*sub;
	int		i;

	paths = ft_get_path(env);
	if (!paths)
		return (1);
	sub = ft_strjoin("/", cmd);
	if (!sub)
		return (1);
	i = 0;
	while (paths[i])
	{
		*cmd_path = ft_strjoin(paths[i], sub);
		if (!*cmd_path)
			return (ft_free_it(paths, sub), 1);
		if (!access(*cmd_path, F_OK))
			return (ft_free_it(paths, sub), 0);
		free(*cmd_path);
		i++;
	}
	ft_free_it(paths, sub);
	return (1);
}
