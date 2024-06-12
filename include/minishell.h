/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:22:14 by claferna          #+#    #+#             */
/*   Updated: 2024/06/12 10:33:43 by ddel-bla         ###   ########.fr       */
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

// ......... FUNCTIONS ..........
//lexer
char	*ft_quotes(char *string);

#endif
