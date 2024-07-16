/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_struct2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:23:05 by claferna          #+#    #+#             */
/*   Updated: 2024/07/13 18:48:29 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Prints a given cmd list.
 */
void	print_cmd(t_cmd *list)
{
	t_cmd	*aux;
	int		i;

	aux = list;
	while (aux != NULL)
	{
		i = 0;
		printf("Command\n");
		while (aux->cmd[i])
		{
			printf("%d argument: \033[0;31m %s \033[0m\n", \
					i, aux->cmd[i]);
			i++;
		}
		printf("Operator type: \033[0;35m%s \033[0m\n", \
				get_str_types(aux->operator_type));
		print_redirs(aux->redirection);
		aux = aux->next;
	}
}

/*
 * Gets an element of a cmd list by his index.
 */
t_cmd	*get_cmd_by_index(t_cmd *cmd, int index)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		if (index == i)
			return (current);
		current = current->next;
		i++;
	}
	return (NULL);
}
