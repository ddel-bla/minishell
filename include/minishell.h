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
# define T_END		-1
# define T_PIPE         0
# define T_RED_IN       1
# define T_RED_OUT      2
# define T_RED_APP      3
# define T_RED_HER      4
# define T_OTHER        5
# define T_LIMIT	6
# define T_OUTFILE	7
# define T_INFILE	8
# define T_COMMAND	9
	
// ............ LIBS ............
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// .......... HEADERS ...........
# include "./lexer.h"
# include "./parser.h"
// .......... STRUCTS ...........

typedef struct s_lexer
{
	char		*input;  //Entrada recibida
	size_t		index;   //Posición actual de la cadena
	struct s_token	*token_list;//Puntero a lista de tokens
}		t_lexer;

// ......... FUNCTIONS ..........
//lexer
char	*ft_quotes(char *string);
int	lexer(char *input, t_token **token_list);
int	get_basic_type(char *token);
void	get_definitive_type(t_token **token_list);
char	*get_str_types(int type);
int	validate_token(char *token);
int	check_syntax(t_token **tokens);
//parser
void	parser(t_token **tokens, t_cmd **cmd);
//lexer-utils
int		ft_strcmp(char *str, char *c);
char	*ft_substr(char *input, int start, int end);
int		ft_isspace(char c);
int		ft_isquote(char c);
int		ft_isspecial(char c);
char	*ft_trim_spaces(char *str);
#endif
