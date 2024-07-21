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
void	treat_expansion(char *input, char *output, t_aux_exp *aux, \
		t_shell *shell)
{
	char	*status_str;

	if (input[aux->i + 1] == '$')
		insert_dollar(output, &aux->out_index, &aux->i);
	else if (input[aux->i + 1] == '"' && input[aux->i + 2] && \
			input[aux->i + 2] == '"')
		(void)status_str;
	else if (input[aux->i + 1] == '"')
		output[aux->out_index++] = '$';
	else if (input[aux->i + 1] == '?')
	{
		status_str = ft_itoa(shell->exit_status);
		ft_strncpy(&output[aux->out_index], status_str, \
				ft_strlen(status_str));
		aux->out_index += ft_strlen(status_str);
		free(status_str);
		aux->i++;
	}
	else
		variable_expansion(input, output, aux, shell->env);
}

/*
 * Count the length of the cases that will be expanded in the
 * expansion process.
 */
void	count_expansion(char *input, t_aux_exp *aux, t_shell *shell)
{
	char	*status_str;

	if (input[aux->i + 1] == '$')
		count_vars(&aux->i, &aux->out_index);
	else if (input[aux->i + 1] == '"')
		aux->out_index++;
	else if (input[aux->i + 1] == '"' && input[aux->i + 2] && \
			input[aux->i + 2] == '"')
		(void)status_str;
	else if (input[aux->i + 1] == '?')
	{
		status_str = ft_itoa(shell->exit_status);
		aux->out_index += ft_strlen(status_str);
		free(status_str);
	}
	else
		count_env_var(input, &aux->i, &aux->out_index, shell->env);
}
