/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:08 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/04 18:55:28 by claferna         ###   ########.fr       */
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
	t_redir	*cu;

	*exp = copy_cmd(shell->cmd);
	current = *exp;
	shell->n_cmds = 0;
	shell->n_hdcs = 0;
	while (current != NULL)
	{
		i = -1;
		while (current->cmd[++i] != NULL)
		{
			current->cmd[i] = expand_quotes(shell, current->cmd[i]);
			cu = current->redirection;
			while (cu != NULL)
			{
				if (!(cu->type == T_RED_HER_EX || cu->type == T_RED_HER))
					cu->file = expand_quotes(shell, cu->file);
				cu = cu->next;
			}
		}
		current = current->next;
		shell->n_cmds++;
	}
}
