/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:52:37 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 16:53:30 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// _________ TOKEN_TYPE _________
# define T_END		-1
# define T_PIPE         0
# define T_RED_IN       1
# define T_RED_OUT      2
# define T_RED_APP      3
# define T_RED_HER      4
# define T_RED_HER_EX	5
# define T_OTHER        6
# define T_LIMIT	7
# define T_OUTFILE	8
# define T_INFILE	9
# define T_COMMAND	10

// .......... STRUCTS ...........
typedef struct s_token
{
	char			*value;
	int				type;
	int				index;
	struct s_token	*next;
}					t_token;

// ......... FUNCTIONS ..........
// ________ token struct ________
t_token	*create_token(char *value, int type, int index);
void	add_token(t_token **list, t_token *token);
t_token	*get_token_by_index(t_token *list, int index);
int		tokens_size(t_token *list);
void	print_tokens(t_token *list);
void	free_tokens(t_token *list);
// ___________ utils ____________
int		get_basic_type(char *token);
void	get_definitive_type(t_token **token_list);
char	*get_str_types(int type);
int		validate_token(char *token);
int		check_syntax(t_token **tokens);
void	post_process_redirs(t_token **tokens);
#endif
