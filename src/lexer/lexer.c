#include "../../include/minishell.h"

static int	process_quotes(t_token **token_list, char *input, int *i);
static void	process(t_token **token_list, char *input, int start, int end);
static int	check_syntax(t_token **token_list);

/*
 * Main function of the lexer process
 */
int	lexer(char *input, t_token **token_list)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			if (process_quotes(token_list, input, &i))
				return (2);
		j = i;
		while (input[i] && !ft_isspace(input[i]) && input[i] != '\'' \
				&& input[i] != '\"')
			i++;
		if (i == j)
			break;
		if (i > j)
			process(token_list, input, j, i - 1);
	}
	get_definitive_type(token_list);
	return (check_syntax(token_list));
}

/*
 * Process tokens with quotations (simple or double)
 */
static int    process_quotes(t_token **token_list, char *input, int *i)
{
        char    quote;
        char    *token;
        int     index;
        int     j;

        quote = input[*i];
        j = (*i) + 1;
        while (input[j] && input[j] != quote)
                j++;
        if (input[j] == quote)
        {
                token = ft_substr(input, (*i), j);
                index = lst_size(*token_list);
                add_token(token_list, create_token(token, T_OTHER, index));
                (*i) = j + 1;
        }
        else
                return (1);
	return (0);
}

/*
 * Process normal tokens (no quotes)
 */
static void	process(t_token **token_list, char *input, int start, int end)
{
	char	*aux;
	int	type;
	int	index;

	aux = ft_substr(input, start, end);
	type = get_basic_type(aux);
	index = lst_size(*token_list);
	add_token(token_list, create_token(aux, type, index));
}

/*
 * Checks sintax based on token order.
 */
static int	check_syntax(t_token **token_list)
{
	t_token *aux;

	aux = *token_list;
	if (aux->type == T_PIPE)
		return (1);
	while (aux)
	{
		if (aux->type == T_PIPE && !aux->next)
			return (1);
		if ((aux->type == T_RED_IN || aux->type == T_RED_HER) && \
                                !aux->next)
                        return (1);
                if ((aux->type == T_RED_OUT || aux->type == T_RED_APP) && \
                                !aux->next)
			return (1);
		if (aux->type == T_PIPE && aux->next->type == T_PIPE)
			return (1);
		if ((aux->type == T_RED_IN || aux->type == T_RED_HER) && \
			       	aux->next->type != T_INFILE)
			return (1);
		if ((aux->type == T_RED_OUT || aux->type == T_RED_APP) && \
				aux->next->type != T_OUTFILE)
			return (1);
		aux = aux->next;
	}
	return (0);
}
/*
int main(void)
{
	t_token *token_list;

	token_list = NULL;
	//En error
	//char *command = "echo \"Hello\" >";
	//char *command = "ls -l |";
	//char *command = "cat <";
	//char *command = "grep \"pattern";
	//char *command = "gcc source.c -o program >";
	//char *command = "| echo \"This is a test";
	//Buenos comandos
	//char *command = "echo \"Hello world!\" > outfile.txt && cat < infile.txt | grep -i \"pattern\"";
	//char *command = "ls -l $HOME.txt | grep \"file\"";
	//char *command = "gcc source.c -o program > errors.log > output.log";
	//char *command = "echo \"Current directory: $(pwd), '$USER'\"";
	//char *command = "command1 < input.txt | command2 | command3 > output.txt";
	//char *command = "cat Makefile >> 1 | > outfile.txt | echo \"HOLA '$PATH'\"";
       	lexer(command, &token_list);
	print_lst(token_list);	
}*/
