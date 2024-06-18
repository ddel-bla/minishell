#include "../../include/minishell.h"

<<<<<<< Updated upstream
static char	**get_cmds(t_token **tokens);
static int	get_operator(t_token **tokens);
static t_redir	*get_redirections(t_token **tokens);

/*
 * Main function of the parser process
 */
void	parser(t_token **tokens, t_cmd **cmd)
{
	t_token	*aux;
	char **args;
	t_redir	*redir;
	int	operator;
	
	aux = *tokens;
	redir = NULL;	
	while (aux) 
	{
		args = get_cmds(&aux);
		redir = get_redirections(&aux);
		operator = get_operator(&aux);
		add_cmd(cmd, create_cmd(args, operator, redir));
=======
void	parser(t_token **tokens, t_cmd **cmd)
{
	t_token	*aux;
	t_redir	*redir;
	int	len;
	int	operator;
	int i;	
	
	aux = *tokens;
	redir = NULL;
	while (aux && aux->next) 
	{
		len = tokens_size(*tokens);
		char **args = (char **)malloc(sizeof(char *) * (len + 1));
        	if (!args)
            		return;

        	i = 0;
		while (aux && aux->type == T_COMMAND)
		{
			args[i] = aux->value;
			aux = aux->next;
			i++;
		}
		args[i] = NULL;
		if (aux && aux->type >= 1 && aux->type <= 4 && aux->next && (aux->next->type == 7 || aux->next->type == 8))
		{
			add_redir(&redir, create_redir(aux->type, aux->next->value));
			aux = aux->next->next;
		}
		if (aux && aux->type == T_PIPE)
                        operator = aux->type; 
		else
                        operator = -1;
		t_cmd *new_cmd = create_cmd(args, operator, redir);
		add_cmd(cmd, new_cmd);
>>>>>>> Stashed changes
		redir = NULL;
		if (aux)
			aux = aux->next;
	}
}
<<<<<<< Updated upstream

/*
 * Extracs the cmd atributes of the token list corresponding to
 * one command and returns them in an array format.
 */
static char	**get_cmds(t_token **token)
{
	int	i;
	int	len;
	char	**args;

	len = tokens_size(*token);
	args = (char **)malloc(sizeof(char *) * len + 1);
	if (!args)
		return (NULL);
	i = 0;
	while ((*token) && (*token)->type == T_COMMAND)
	{
		args[i] = (*token)->value;
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
=======
>>>>>>> Stashed changes
/*
int main() {
	t_token *tokens = NULL;	
	//char *command = "echo Hello > outfile.txt | cat < infile.txt | grep -i \"pattern\"";
	char *command = "cat Makefile >> 1 | echo \"HOLA '$PATH'\"";
        lexer(command, &tokens);
	print_tokens(tokens);
	t_cmd *cmd_list = NULL;
    parser(&tokens, &cmd_list);

	print_cmd(cmd_list);
    return 0;
}*/
