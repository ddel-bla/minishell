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
static int	check_syntax(t_token **tokens);

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
	int		type;
	int		i;
	int		k;
	int		index;

	if (start > end)
		return (1);
	i = 0;
	aux = ft_substr(input, start, end);
	if (!validate_token(aux))
		return (1);
	type = get_basic_type(aux);
	index = tokens_size(*tokens);
	add_token(tokens, create_token(aux, type, index));
	return (0);
}

/*
 * Checks sintax based on token order.
 */
static int	check_syntax(t_token **tokens)
{
	t_token	*t;

	t = *tokens;
	if (t->type == T_PIPE)
		return (1);
	while (t)
	{
		if (t->type == T_PIPE && !t->next)
			return (1);
		if ((t->type == T_RED_IN || t->type == T_RED_HER) && !t->next)
			return (1);
		if ((t->type == T_RED_OUT || t->type == T_RED_APP) && !t->next)
			return (1);
		if (t->type == T_PIPE && t->next->type == T_PIPE)
			return (1);
		if (t->type == T_RED_IN && t->next->type != T_INFILE)
			return (1);
		if (t->type == T_RED_HER && t->next->type != T_LIMIT)
			return (1);
		if ((t->type == T_RED_OUT || t->type == T_RED_APP) && \
				t->next->type != T_OUTFILE)
			return (1);
		t = t->next;
	}
	return (0);
}
