#ifndef LEXER_H
# define LEXER_H

// .......... STRUCTS ...........
typedef struct s_token
{
	char		*value;
	int		type;
	int		index;
	struct s_token	*next;
}		t_token;

// ......... FUNCTIONS ..........
t_token	*create_token(char *value, int type, int index);
void	add_token(t_token **list, t_token *token);
t_token	*get_token_by_index(t_token *list, int index);
int	tokens_size(t_token *list);
void	print_tokens(t_token *list);
void	free_tokens(t_token *list);
#endif
