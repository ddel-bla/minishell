/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:56:02 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/23 19:16:34 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*ft_add_var(char *line, char *var)
{
	char	*new;

	new = ft_strjoin(line, var);
	free(line);
	return (new);
}

static char	*exp_dollar(char *cmd, t_shell *shell, char **new)
{
	char	*var_name;
	t_env	*myenv;
	char	*aux;
	int		i;

	i = 0;
	if (cmd[i] == '?')
	{
		aux = ft_strjoin(*new, ft_itoa(shell->exit_status));
		free(*new);
		*new = aux;
		return (cmd + 1);
	}
	while (cmd[i] != ' ' && cmd[i] != '$' && cmd[i] != '\''
		&& cmd[i] != '\"' && cmd[i] != '\0' && cmd[i] != '\n')
		i++;
	if (i == 0)
		return (cmd + 1);
	var_name = ft_substr(cmd, 0, i - 1);
	myenv = get_env_by_name(shell->env, var_name);
	free(var_name);
	if (myenv)
		*new = ft_add_var(*new, myenv->value);
	return (cmd + i);
}

static char	*ft_add(char *line, int len, char **new)
{
	char	*add;
	char	*aux;

	add = ft_substr(line, 0, len);
	aux = ft_strjoin(*new, add);
	free(add);
	free(*new);
	*new = aux;
	return (line + len + 1);
}

char	*here_expand(char *line, t_shell *shell)
{
	char	*new;
	int		i;

	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			line = exp_dollar(++line, shell, &new);
		else
		{
			while (line[i] != '\0' && line[i] != '\n' && line[i] != '$')
				i++;
			if (line[i] == '$')
				i--;
			line = ft_add(line, i, &new);
		}
		i = 0;
	}
	return (new);
}
