/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:25:54 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:34:02 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**add_to_args(char **args, t_token **tokens)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	while (args && args[count])
		count++;
	while (*tokens && (*tokens)->type == T_COMMAND)
	{
		new_args = malloc((count + 2) * sizeof(char *));
		i = 0;
		while (i < count)
		{
			new_args[i] = args[i];
			i++;
		}
		new_args[count] = strdup((*tokens)->value);
		new_args[count + 1] = NULL;
		free(args);
		args = new_args;
		count++;
		*tokens = (*tokens)->next;
	}
	return (args);
}
