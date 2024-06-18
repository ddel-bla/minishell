/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:01:10 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 18:52:02 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	extract_tokens(t_token **tokens, char *input);
static int	process_quotes(t_token **tokens, char *input, int *i);
static int	process(t_token **tokens, char *input, int start, int end);
//static int	add_indv_token(t_token **tokens, char *aux, int start, int end);

/*
 * Main function of the lexer process
 */
int	lexer(char *input, t_token **tokens)
{
	ft_trim_spaces(input);
	if (extract_tokens(tokens, input))
		return (1);
	get_definitive_type(tokens);
	return (check_syntax(tokens));
}

/*
 * Extract the tokens from the input.
 * - In stands for input.
 */
static	int	extract_tokens(t_token **tokens, char *in)
{
	int	i;
	int	j;

	i = 0;
	while (in[i])
	{
		while (in[i] && ft_isspace(in[i]))
			i++;
		if (!in[i])
			return (1);
		if (in[i] && ft_isquote(in[i]))
		{
			if (process_quotes(tokens, in, &i))
				return (1);
			continue ;
		}
		j = i;
		while (in[i] && !ft_isspace(in[i]))
			i++;
		if (process(tokens, in, j, i - 1))
			return (1);
		if (i == j)
			break ;
	}
	return (0);
}

/*
 * Process tokens with quotations (simple or double)
 */
static int	process_quotes(t_token **tokens, char *input, int *i)
{
	char	quote;
	char	*token;
	int		index;
	int		j;

	quote = input[*i];
	j = (*i) + 1;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] == quote)
	{
		token = ft_substr(input, (*i), j);
		index = tokens_size(*tokens);
		add_token(tokens, create_token(token, T_OTHER, index));
		(*i) = j + 1;
	}
	else
		return (1);
	return (0);
}

/*
 * Process normal tokens (no quotes)
 */
static int	process(t_token **tokens, char *input, int start, int end)
{
	char	*aux;
	int	type;
	int 	index;
	int	i;
	int	k;

	if (start > end)
		return (1);
	aux = ft_substr(input, start, end);
	i = 0;
	while (aux[i])
	{
		k = i;
		while (aux[i] && !ft_isspecial(aux[i]))
			i++;
		if (i > k)
		{
			char *a = ft_substr(aux, k, i - 1);
			if (validate_token(a))
				return (1);
			type = get_basic_type(a);
			index = tokens_size(*tokens);
			add_token(tokens, create_token(a, type, index));
		}
		k = i;
		while (aux[i] && ft_isspecial(aux[i]))
			i++;
		if (i > k)
		{
			char *a2 = ft_substr(aux, k, i -1);
			if (validate_token(a2))
				return (1);
			type = get_basic_type(a2);
			index = tokens_size(*tokens);
			add_token(tokens, create_token(a2, type, index));
		}
	}
	return 0;
}
/*
static	int	add_indv_token(t_token **tokens, char *aux, int start, int end)
{
	int	type;
	int	index;
	char	*token;

	token = ft_substr(aux, start, end);
	if (validate_token(token))
		return (1);
	type = get_basic_type(token);
	index = tokens_size(*tokens);
	add_token(tokens, create_token(token, type, index));
	return (0);
}*/
