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
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	cmd = NULL;
	while (1)
	{
		input = readline("minishell>$");
		// clean input start and end spaces(\t\s\v...)
		//if (*input)
			//TODO history
		if (*input)
		{
			if (lexer(input, &tokens))
				printf("Error sintáctico\n");
<<<<<<< Updated upstream
			print_tokens(tokens);
		}
		parser(&tokens, &cmd);
		print_cmd(cmd);
		free_cmd(cmd);
		cmd = NULL;
		free_tokens(tokens);
		tokens =  NULL;
=======
			else
				print_tokens(tokens);
		}
		parser(&tokens, &cmd);
		printf(" AD %s", cmd->cmd[0]);
		print_cmd(cmd);
		printf("asd");
		print_cmd(cmd);
		free_cmd(cmd);
		free_tokens(tokens);
		tokens =  NULL;
		//parseer
>>>>>>> Stashed changes
		//expander
		//executor
		//free
		free(input);
	}
}
