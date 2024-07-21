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

#include "../../../include/minishell.h"

/*
 * Expands environments varibales when necessary in the expansion process.
 */
void	variable_expansion(char *input, char *output, t_aux_exp *a, t_env *env)
{
	int		var_start;
	int		var_len;
	char	*var_name;
	t_env	*var;

	var_start = ++(a->i);
	while (a->i < ft_strlen(input) && (isalpha(input[a->i]) \
				|| input[a->i] == '_'))
		a->i++;
	var_len = a->i - var_start;
	var_name = (char *)malloc(var_len + 1);
	if (!var_name)
		exit(EXIT_FAILURE);
	strncpy(var_name, &input[var_start], var_len);
	var_name[var_len] = '\0';
	var = get_env_by_name(env, var_name);
	free(var_name);
	if (var && var->value)
	{
		strncpy(&output[a->out_index], var->value, strlen(var->value));
		a->out_index += strlen(var->value);
	}
	a->i--;
}

/*
 * Counts the length of the environmental variable that will be replaced in
 * the expansion process.
 */
void	count_env_var(char *input, int *index, int *length, t_env *env)
{
	int		var_start;
	int		var_len;
	char	*var_name;
	t_env	*var;

	var_start = ++(*index);
	while (input[*index] && (isalpha(input[*index]) || input[*index] == '_'))
		(*index)++;
	var_len = *index - var_start;
	var_name = (char *)malloc(var_len + 1);
	if (!var_name)
		exit(EXIT_FAILURE);
	strncpy(var_name, &input[var_start], var_len);
	var_name[var_len] = '\0';
	var = get_env_by_name(env, var_name);
	free(var_name);
	if (var && var->value)
		*length += ft_strlen(var->value);
	(*index)--;
}

/*
 * Inserts a dollar when dealing with continuous dollars 
 * in the expansion process.
 */
void	insert_dollar(char *output, int *out_index, int *i)
{
	output[(*out_index)++] = '$';
	(*i)++;
}

/*
 * Increments i and size through pointers.
 */
void	count_vars(int *i, int *size)
{
	(*i)++;
	(*size)++;
}

/*
 * Initiliaze aux structure.
 */
void	init_aux(t_aux_exp *aux)
{
	aux->out_index = 0;
	aux->s_quotes = 0;
	aux->d_quotes = 0;
	aux->i = -1;
}
