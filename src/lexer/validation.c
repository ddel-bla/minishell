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

static int	validate_special_chars(char *token);
static int	validate_inner_quotes(char *token);

/*
 * All validations of the token char in one.
 */
int	validate_token(char *token)
{
	if (validate_special_chars(token))
		return (1);
	if (validate_inner_quotes(token))
		return (1);
	return (0);
}

/*
 * Checks sintax based on token order.
 */
int	check_syntax(t_token **tokens)
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

/*
 * Validates if a token contains more than 2 consecutives special caracteres.
 */
static int	validate_special_chars(char *token)
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
			return (1);
		i++;
	}
	return (0);
}

/*
 * Checks wheter inner quotes are closed.
*/
static int	validate_inner_quotes(char *token)
{
	int	i;
	int	count;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\"' || token[i] == '\'')
			count++;	
		i++;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}
