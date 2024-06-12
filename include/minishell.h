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
# define PROMPT 'minishell>$'
	
// ............ LIBS ............
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
// .......... STRUCTS ...........
typedef struct s_lexer
{
		char           *input;  //Entrada recibida
		size_t         index;   //Posición actual de la cadena
		struct s_token *token_list;//Puntero a lista de tokens
}            t_lexer;

typedef struct s_token
{
			char           *value;  //Valor del token
			int             type;   //Tipo del token
			int             index;  //Posición del token
			struct s_token *next;   //Siguiente elemento
}            t_token;

// ......... FUNCTIONS ..........
//lexer
char	*ft_quotes(char *string);

#endif
