/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:08 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/03 15:30:33 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Calculates the number of characters a expanded string will have in order
 * to be able to allcate it in the future.
 */
int	calculate_expanded_size(char *input, t_env *env)
{
	t_aux_exp	aux;

	init_aux(&aux);
	while (++aux.i < ft_strlen(input))
	{
		if (input[aux.i] == '\'')
		{
			if (!aux.d_quotes)
				aux.s_quotes = !aux.s_quotes;
			aux.out_index++;
		}
		else if (input[aux.i] == '"')
		{
			aux.d_quotes = !aux.d_quotes;
			aux.out_index++;
		}
		else if (input[aux.i] == '$' && !aux.s_quotes \
				&& aux.i + 1 < ft_strlen(input))
			count_expansion(input, &aux, env);
		else
			aux.out_index++;
	}
	return (aux.out_index + 1);
}

/*
 * Expands the given string if applicable.
 */
void	expand(char *input, char *output, t_env *env)
{
	t_aux_exp	aux;

	init_aux(&aux);
	while (++aux.i < ft_strlen(input))
	{
		if (input[aux.i] == '\'')
		{
			if (!aux.d_quotes)
				aux.s_quotes = !aux.s_quotes;
			output[aux.out_index++] = input[aux.i];
		}
		else if (input[aux.i] == '"')
		{
			aux.d_quotes = !aux.d_quotes;
			output[aux.out_index++] = input[aux.i];
		}
		else if (input[aux.i] == '$' && !aux.s_quotes \
				&& aux.i + 1 < ft_strlen(input))
			treat_expansion(input, output, &aux, env);
		else
			output[aux.out_index++] = input[aux.i];
	}
	output[aux.out_index] = '\0';
}
