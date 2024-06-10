/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:18:35 by claferna          #+#    #+#             */
/*   Updated: 2024/06/10 18:30:27 by claferna         ###   ########.fr       */
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

	while (1)
	{
		input = readline("minishell>$");
		// clean input start and end spaces(\t\s\v...)
		//if (*input)
			//TODO history
		//lexer
		//parseer
		//expander
		//executor
		//free
		free(input);
	}
}
