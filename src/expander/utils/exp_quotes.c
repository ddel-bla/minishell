/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:05 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/24 17:30:23 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_status(char *cmd, t_shell *shell, char **new)
{
	char	*aux;

	aux = ft_strjoin(*new, ft_itoa(shell->exit_status));
	free(*new);
	*new = aux;
	return (cmd + 2);
}

char	*dollar(char *cmd, t_shell *shell, char **new)
{
	char	*var_name;
	t_env	*myenv;
	int		i;

	i = 1;
	if (cmd[i] == '?')
		return (ft_status(cmd, shell, new));
	while (cmd[i] != '\0' && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	if (i == 1)
		*new = ft_add_var(*new, "$");
	else
	{
		var_name = ft_substr(cmd, 1, i - 1);
		myenv = get_env_by_name(shell->env, var_name);
		free(var_name);
		if (myenv)
			*new = ft_add_var(*new, myenv->value);
	}
	return (cmd + i);
}

char	*quote(char *cmd, char **new)
{
	char	*start;
	char	*add;
	char	*aux;

	start = cmd;
	while (*cmd != '\"' && *cmd != '\'' && *cmd != '$' && *cmd != '\0')
		cmd++;
	if (cmd != start)
	{
		add = ft_substr(start, 0, cmd - start - 1);
		aux = ft_strjoin(*new, add);
		free(*new);
		free(add);
		*new = aux;
	}
	return (cmd);
}

char	*dquote(char *cmd, t_shell *shell, char **new)
{
	int		i;
	char	*add;
	char	*aux;

	i = 0;
	while (cmd[i] != '\"')
	{
		if (cmd[i] == '$')
			cmd = dollar(cmd, shell, new);
		else
		{
			while (cmd[i] != '\"' && cmd[i] != '$')
				i++;
			add = ft_substr(cmd, 0, i - 1);
			aux = ft_strjoin(*new, add);
			free(*new);
			free(add);
			*new = aux;
			cmd += i;
		}
		i = 0;
	}
	return (cmd + 1);
}

char	*squote(char *cmd, char **new)
{
	int		i;
	char	*add;
	char	*aux;

	i = 1;
	while (cmd[i] != '\'')
		i++;
	if (i == 1)
		return (cmd + 2);
	add = ft_substr(cmd, 1, i - 1);
	aux = ft_strjoin(*new, add);
	free(*new);
	free(add);
	*new = aux;
	return (cmd + i + 1);
}
