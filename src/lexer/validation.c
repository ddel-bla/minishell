/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:16:46 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 18:30:17 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Validates if a token contains more than 2 consecutives special caracteres.
 */
int	validate_token(char *token)
{
	int	i;
	int	times_redir;
	int	times_pipe;

	i = 0;
	while (token[i])
	{
		times_redir = 0;
		while (token[i] && (token[i] == '<' || token[i] == '>'))
		{
			times_redir++;
			i++;
		}
		times_pipe = 0;
		while (token[i] && token[i] == '|')
		{
			times_pipe++;
			i++;
		}
		if (times_redir > 2 || times_pipe > 1)
			return (0);
		i++;
	}
	return (1);
}

/*
 * Checks wheter inner quotes are closed
*/
int	validate_inner_quotes(char *token)
{
	int	i;
	int	count;

	i = 0;
	while (token[i])
	{	
		count = 0;
		if (token[i] == '\"' || token[i] == '\'')
		{
			while (token[i] && (token[i] == '\"' || token[i] == '\''))
			{
				count++;
				i++;
			}
			if (count % 2 != 0)
				return (0);
		}
		printf("Fuera %c", token[i]);
		i++;
	}
	return (1);
}
