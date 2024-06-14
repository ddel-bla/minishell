/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:18:35 by claferna          #+#    #+#             */
/*   Updated: 2024/06/12 09:31:04 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	start_minishell(void);

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (1);
	(void)argv;
	(void)envp;
	start_minishell();
	return (0);
}

void	start_minishell(void)
{
	char	*input;
	t_token	*token;

	token = NULL;
	(void)token;
	while (1)
	{
		input = readline("minishell>$");
		// clean input start and end spaces(\t\s\v...)
		//if (*input)
			//TODO history
		if (lexer(input, &token))
			printf("Error sintáctico\n");
		else
			print_lst(token);
		free_lst(token);
		token =  NULL;
		//parseer
		//expander
		//executor
		//free
		free(input);
	}
}
