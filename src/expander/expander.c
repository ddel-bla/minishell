/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:08 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/17 10:28:45 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_quotes(t_shell *shell, char *cmd)
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
			ptr = dquote(ptr + 1, shell, &new);
		else if (*ptr == '\'')
			ptr = squote(ptr, &new);
		else if (*ptr == '$')
			ptr = dollar(ptr, shell, &new);
		else
			ptr = quote(ptr, &new);
	}
	free(cmd);
	return (new);
}

void	expander(t_shell *shell, t_cmd **exp)
{
	int		i;
	t_cmd	*current;

	*exp = copy_cmd(shell->cmd);
	current = *exp;
	while (current != NULL)
	{
		i = -1;
		while (current->cmd[++i] != NULL)
			current->cmd[i] = expand_quotes(shell, current->cmd[i]);
		current = current->next;
	}
}
