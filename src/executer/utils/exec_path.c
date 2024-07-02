/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 19:01:23 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/02 15:58:45 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static size_t	ft_strlenchr(const char *s, int c)
{
	size_t	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}
static void	ft_free_it(char **tab, char *prog, char *sub)
{
	int	i;

	i = 0;
	free(prog);
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
	tab = ft_split(myenv->value, ':');
	return (tab);
}

char	*ft_find_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*cmd_path;
	char	*prog;
	char	*sub;
	int		i;

	paths = ft_get_path(env);
	if (!paths)
		return (NULL);
	prog = ft_substr(cmd, 0, ft_strlenchr(cmd, 32));
	sub = ft_strjoin("/", prog);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], sub);
		if (!cmd_path)
			return (NULL);
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		i++;
	}
	ft_free_it(paths, prog, sub);
	return (cmd_path);
}
