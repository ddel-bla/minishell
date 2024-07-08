/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:10:39 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:10:40 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Treats cases of expansion in the expansion process.
 */
void	treat_expansion(char *input, char *output, t_aux_exp *aux, void *env)
{
	if (input[aux->i + 1] == '$')
		insert_dollar(output, &aux->out_index, &aux->i);
	else if (input[aux->i + 1] == '"')
		output[aux->out_index++] = '$';
	else
		variable_expansion(input, output, aux, env);
}

/*
 * Count the length of the cases that will be expanded in the
 * expansion process.
 */
void	count_expansion(char *input, t_aux_exp *aux, void *env)
{
	if (input[aux->i + 1] == '$')
		count_vars(&aux->i, &aux->out_index);
	else if (input[aux->i + 1] == '"')
		aux->out_index++;
	else
		count_env_var(input, &aux->i, &aux->out_index, env);
}
