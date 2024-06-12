#include "../../include/minishell.h"

/*
 * Given a token returns its basic type (redirection, pipes or other)
 */
int	get_basic_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return T_PIPE;
	else if (!ft_strcmp(token, ">"))
		return T_RED_OUT;
	else if (!ft_strcmp(token, ">>"))
		return T_RED_APP;
	else if (!ft_strcmp(token, "<"))
		return T_RED_IN;
	else if (!ft_strcmp(token, "<<"))
		return T_RED_HER;
	return T_OTHER;
}

/*
 * Given a token returns its typ
 */
void	get_definitive_type(t_token **token_list)
{
	t_token *aux;
	
	aux = *token_list;
	if (aux->type == T_OTHER)
		aux->type = T_COMMAND;
	while (aux->next)
	{
		if (aux->type == T_RED_IN && aux->next->type == T_OTHER)
			aux->next->type = T_INFILE;
		else if (aux->type == T_RED_OUT && aux->next->type == T_OTHER)
			aux->next->type = T_OUTFILE;
		else if (aux->type == T_RED_APP && aux->next->type == T_OTHER)
			aux->next->type = T_OUTFILE;
		else if (aux->type == T_RED_HER && aux->next->type == T_OTHER)
			aux->next->type = T_LIMIT;
		else if (aux->type == T_LIMIT && aux->next->type == T_OTHER)
			aux->next->type = T_COMMAND;
		else if (aux->type == T_PIPE && aux->next->type == T_OTHER)
			aux->next->type = T_COMMAND;
		else if (aux->type == T_INFILE && aux->next->type == T_OTHER)
			aux->next->type = T_COMMAND;
		else if (aux->type == T_OUTFILE && aux->next->type == T_OTHER)
			aux->next->type = T_COMMAND;
		else if (aux->type == T_COMMAND && aux->next->type == T_OTHER)
			aux->next->type = T_COMMAND;
		aux = aux->next;
	}
}

/*
 * Return the str form of the selected type.
 */
char	*get_str_types(int type)
{
	if (type == T_PIPE)
		return "PIPE";
	else if (type == T_RED_OUT)
		return "OUT REDIRECTION";
	else if (type == T_RED_IN)
		return "IN_REDIRECTION";
	else if (type == T_RED_HER)
		return "HEREDOC REDIRECTION";
	else if (type == T_LIMIT)
		return "HEREDOC LIMITER";
	else if (type == T_RED_APP)
		return "APPEND REDIRECTION";
	else if (type == T_OUTFILE)
		return "OUTFILE";
	else if (type == T_INFILE)
		return "INFILE";
	else if (type == T_COMMAND)
		return "COMMAND";
	return "OTHER";
}
