#include "../../include/minishell.h"

static char	**get_cmds(t_token **tokens);
static int	get_operator(t_token **tokens);
static t_redir	*get_redirections(t_token **tokens);

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
		redir = NULL;
		if (aux)
			aux = aux->next;
	}
}

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

static	int	get_operator(t_token **token)
{

	if (*token && (*token)->type == T_PIPE)
		return ((*token)->type);
	return (-1);
}

static t_redir	*get_redirections(t_token **token)
{
	t_redir	*redir;

	redir = NULL;
	while (*token && (*token)->type >= 1 && (*token)->type <= 4 \
		&& (*token)->next && ((*token)->next->type == 7 \
		|| (*token)->next->type == 8))
	{
		add_redir(&redir, create_redir((*token)->type, (*token)->next->value));
		*token = (*token)->next->next;
	}
	return (redir);
}
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
