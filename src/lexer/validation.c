/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:16:46 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:17:02 by claferna         ###   ########.fr       */
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
