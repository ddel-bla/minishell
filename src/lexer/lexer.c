#include "../../include/minishell.h"

static void	process_quotes(t_token **token_list, char *input, int *i);
static void	process(t_token **token_list, char *input, int start, int end);
static int	get_type(char *token);

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
}

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

static void	process(t_token **token_list, char *input, int start, int end)
{
	char	*aux;
	int	type;
	int	index;

	aux = ft_substr(input, start, end);
	type = get_type(aux);
	index = lst_size(*token_list);
	add_token(token_list, create_token(aux, type, index));
}


static int get_type(char *token)
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
