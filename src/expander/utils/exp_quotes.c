/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:05 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/03 15:46:37 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*dollar(char *cmd, t_env *list, char **new)
{
	char	*start;
	char	*var_name;
	t_env	*myenv;
	char	*aux;

	start = ++cmd;
	while (*cmd != ' ' && *cmd != '$' && *cmd != '\''
		&& *cmd != '\"' && *cmd != '\0')
		cmd++;
	var_name = ft_substr(start, 0, cmd - start - 1);
	myenv = get_env_by_name(list, var_name);
	free(var_name);
	if (myenv)
	{
		aux = ft_strjoin(*new, myenv->value);
		free(*new);
		*new = aux;
	}
	return (cmd);
}

static char	*quote(char *cmd, char **new)
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

static char	*dquote(char *cmd, t_env *list, char **new)
{
	char	*start;
	char	*add;
	char	*aux;

	start = ++cmd;
	if (*cmd == '\"')
		return (cmd + 1);
	while (*cmd != '\"')
	{
		if (*cmd == '$')
		{
			cmd = quote(start, new);
			cmd = dollar(cmd, list, new);
			start = cmd;
		}
		else
			cmd++;
	}
	if (*cmd == '\"')
		return (cmd + 1);
	add = ft_substr(start, 0, cmd - start - 1);
	aux = ft_strjoin(*new, add);
	free(*new);
	*new = aux;
	return (free(add), cmd + 1);
}

static char	*squote(char *cmd, char **new)
{
	char	*start;
	char	*add;
	char	*aux;

	start = ++cmd;
	if (*cmd == '\'')
		return (cmd + 1);
	while (*cmd != '\'')
		cmd++;
	add = ft_substr(start, 0, cmd - start - 1);
	aux = ft_strjoin(*new, add);
	free(*new);
	free(add);
	*new = aux;
	return (cmd + 1);
}

char	*expand_quotes(t_env *list, char *cmd)
{
	char	*new;
	char	*ptr;

	if (!cmd)
		return (NULL);
	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	ptr = cmd;
	while (*ptr != '\0')
	{
		if (*ptr == '\"')
			ptr = dquote(ptr, list, &new);
		else if (*ptr == '\'')
			ptr = squote(ptr, &new);
		else if (*ptr == '$')
			ptr = dollar(ptr, list, &new);
		else
			ptr = quote(ptr, &new);
	}
	free(cmd);
	return (new);
}
