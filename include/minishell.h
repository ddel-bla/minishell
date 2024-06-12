/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:22:14 by claferna          #+#    #+#             */
/*   Updated: 2024/06/12 15:37:44 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

// ........... MACROS ...........
// __________ visuals ___________
# define PROMPT "minishell>$"
// _________ TOKEN_TYPE _________
# define T_PIPE         0
# define T_RED_IN       1
# define T_RED_OUT      2
# define T_RED_HER      3
# define T_RED_APP      4
# define T_OTHER        5

	
// ............ LIBS ............
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
// .......... STRUCTS ...........
typedef struct s_lexer
{
	char		*input;  //Entrada recibida
	size_t		index;   //Posición actual de la cadena
	struct s_token	*token_list;//Puntero a lista de tokens
}		t_lexer;

typedef struct s_token
{
	char		*value;  //Valor del token
	int		type;   //Tipo del token
	int		index;  //Posición del token
	struct s_token	*next;   //Siguiente elemento
}			t_token;

// ......... FUNCTIONS ..........
//lexer
char	*ft_quotes(char *string);
void	lexer(char *input, t_token **token_list);
//lexer-utils
t_token *create_token(char *value, int type, int index);
int     lst_size(t_token *list);
t_token	*lst_last(t_token *list);
void    add_token(t_token **list, t_token *token);
void    print_lst(t_token *list);
void	free_lst(t_token *list);
t_token *get_token_by_index(t_token *token_list, int index);
int     ft_strcmp(char *str, char *c);
char    *ft_substr(char *input, int start, int end);
#endif
