#include "../../include/minishell.h"

static void	process_quotes(t_token **token_list, char *input, int *i);
static void	process(t_token **token_list, char *input, int start, int end);
static int	check_syntax(t_token **token_list);

/*
 * Main function of the lexer process
 */
void	lexer(char *input, t_token **token_list)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ') //cambiar a isspace()
			i++;
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
		{
			process_quotes(token_list, input, &i);
			continue;
		}
		j = i;
		while (input[i] && input[i] != ' ' && input[i] != '\'' \
				&& input[i] != '\"')
			i++;
		if (i > j)
			process(token_list, input, j, i - 1);
	}
	get_definitive_type(token_list);
	printf("%d", check_syntax(token_list));
}

/*
 * Process tokens with quotations (simple or double)
 */
static void    process_quotes(t_token **token_list, char *input, int *i)
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
                token = ft_substr(input, (*i) + 1, j - 1);
                index = lst_size(*token_list);
                add_token(token_list, create_token(token, T_OTHER, index));
                (*i) = j + 1;
        }
        else
                printf("Error en las comillas\n");
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
	while (aux)
	{
		if (aux->type == T_PIPE && !aux->next)
			return (0);
		if ((aux->type == T_RED_IN || aux->type == T_RED_HER) && \
                                !aux->next)
                        return (0);
                if ((aux->type == T_RED_OUT || aux->type == T_RED_APP) && \
                                !aux->next)
			return (0);
		if (aux->type == T_PIPE && aux->next->type == T_PIPE)
			return (0);
		if ((aux->type == T_RED_IN || aux->type == T_RED_HER) && \
			       	aux->next->type != T_INFILE)
			return (0);
		if ((aux->type == T_RED_OUT || aux->type == T_RED_APP) && \
				aux->next->type != T_OUTFILE)
			return (0);
		aux = aux->next;
	}
	return (1);
}
/*
int main(void)
{
	t_token *token_list;

	token_list = NULL;
	char *command = "cat Makefile >> 1 | > outfile.txt | echo \"HOLA '$PATH'\"";
       	lexer(command, &token_list);
	print_lst(token_list);	
}*/
