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
static int	process_special(t_token **tokens, char *input, int *i);

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

	i = 0;
	while (in[i])
	{
		while (in[i] && ft_isspace(in[i]))
			i++;
		if (!in[i])
			return (1);
		if (in[i] && !ft_isspecial(in[i]))
		{
			if (process_quotes(tokens, in, &i))
				return (1);
		}
		else if (in[i] && ft_isspecial(in[i]))
			if (process_special(tokens, in, &i))
				return (1);
	}
	return (0);
}

/*
 * Process tokens with quotations (simple or double)
 */
static int	process_quotes(t_token **tokens, char *input, int *i)
{
	int	j;
	char	quote;
	char	*token;

	j = (*i);
	while (input[j] && !ft_isspace(input[j]) && !ft_isspecial(input[j]))
	{
		if (input[j] == '\'' || input[j] == '\"')
		{
			quote = input[j];
			j++;
			while (input[j] && input[j] != quote)
				j++;
			if (input[j] != quote)
				return (1);
		}
		j++;
	}
	if (j == *i)
		return (1);
	token = ft_substr(input, (*i), j - 1);
	add_token(tokens, create_token(token, T_OTHER, tokens_size(*tokens)));
	(*i) = j;
	return (0);
}

/*
 * Process normal tokens (no quotes)
 */
static int	process_special(t_token **tokens, char *input, int *i)
{
	char	*token;
	int	index;
	int	type;
	int	j;

	j = (*i);
	while (input[j] && ft_isspecial(input[j]))
		j++;
	token = ft_substr(input, (*i), j - 1);
	(*i) = j;
	if (validate_token(token))
		return (1);
	type = get_basic_type(token);
	index = tokens_size(*tokens);
	add_token(tokens, create_token(token, type, index));
	return (0);
}
