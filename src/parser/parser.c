/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:20:53 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 17:22:50 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char		**get_cmds(t_token **tokens);
static int		get_operator(t_token **tokens);
static t_redir	*get_redirections(t_token **tokens);

/*
 * Main function of the parser process
 */
void	parser(t_token **tokens, t_cmd **cmd)
{
	t_token	*aux;
	char	**args;
	t_redir	*redir;
	int		operator;

	aux = *tokens;
	redir = NULL;
	while (aux)
	{
		args = get_cmds(&aux);
		redir = get_redirections(&aux);
		operator = get_operator(&aux);
		add_cmd(cmd, create_cmd(args, operator, redir));
		redir = NULL;
		if (aux)
			aux = aux->next;
	}
}

/*
 * Extracs the cmd atributes of the token list corresponding to
 * one command and returns them in an array format.
 */
static char	**get_cmds(t_token **token)
{
	int		i;
	int		len;
	char	**args;

	len = tokens_size(*token);
	args = (char **)malloc(sizeof(char *) * len + 1);
	if (!args)
		return (NULL);
	i = 0;
	while ((*token) && (*token)->type == T_COMMAND)
	{
		args[i] = ft_strdup((*token)->value);
		(*token) = (*token)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/*
 * Extracts the operator atribute of the token list corresponding to
 * one command and returns it in an int format.
 */
static	int	get_operator(t_token **token)
{
	if (*token && (*token)->type == T_PIPE)
		return ((*token)->type);
	return (-1);
}

/*
 * Extracts all the redirections atributes of the token list corresponding to
 * one command and returns it in a t_redir struct format.
 */
static t_redir	*get_redirections(t_token **token)
{
	t_redir	*redir;

	redir = NULL;
	while (*token && (*token)->type >= T_RED_IN \
			&& (*token)->type <= T_RED_HER \
			&& (*token)->next \
			&& ((*token)->next->type == T_OUTFILE \
			|| (*token)->next->type == T_INFILE \
			|| (*token)->next->type == T_LIMIT))
	{
		add_redir(&redir, create_redir((*token)->type, (*token)->next->value));
		*token = (*token)->next->next;
	}
	return (redir);
}
