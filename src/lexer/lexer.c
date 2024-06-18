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
			continue;
		}
		j = i;
		while (in[i] && !ft_isspace(in[i]) && !ft_isquote(in[i]))
			i++;
		if (process(tokens, in, j, i - 1))
			return (1);
		if (i == j)
			break;
	}
	return (0);
}
/*
 * Process tokens with quotations (simple or double)
 */
static int    process_quotes(t_token **tokens, char *input, int *i)
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
	int	index;

	if (start > end)
		return (1);
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
	t_token *aux;

	aux = *tokens;
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
		if (aux->type == T_RED_IN && aux->next->type != T_INFILE)
			return (1);
		if (aux->type == T_RED_HER && aux->next->type != T_LIMIT)
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
	char *command = "grep \"pattern";
//	char *command = "gcc source.c -o program >";
	//char *command = "| echo \"This is a test";
	//Buenos comandos
	//char *command = "echo \"Hello world!\" > outfile.txt && cat < infile.txt | grep -i \"pattern\"";
	//char *command = "ls -l $HOME.txt | grep \"file\"";
	//char *command = "gcc source.c -o program > errors.log > output.log";
	//char *command = "echo \"Current directory: $(pwd), '$USER'\"";
	//char *command = "command1 < input.txt | command2 | command3 > output.txt";
	//char *command = "cat Makefile >> 1 | > outfile.txt | echo \"HOLA '$PATH'\"";
       	lexer(command, &token_list);
	print_tokens(token_list);	
}*/
