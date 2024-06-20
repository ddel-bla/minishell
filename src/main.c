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

void	start_minishell(char **envp);
t_shell	*init(char **envp);

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (1);
	(void)argv;
	(void)envp;
	start_minishell(envp);
	return (0);
}

t_shell	*init(char **envp)
{
	t_shell	*shell;
	t_env	*env;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	env = NULL;
	shell->token = NULL;
	shell->cmd = NULL;
	//save_env(&env, envp);
	//shell->env = env;
	return (shell);
}

void	start_minishell(char **envp)
{
	char	*input;
	t_shell	*shell;

	shell = init(envp);
	//ft_env(shell->env);
	while (1)
	{
		input = readline("minishell>$");
		//if (*input)
			//TODO history
		if (*input)
		{
			if (lexer(input, &shell->token))
				printf("Error sintáctico\n");
			else
				print_tokens(shell->token);
		}
		parser(&shell->token, &shell->cmd);
		print_cmd(shell->cmd);
		free_cmd(shell->cmd);
		free_tokens(shell->token);
		shell->token = NULL;
		shell->cmd = NULL;
		//expander
		//executor
		//free
		free(input);
	}
	free_env(shell->env);
	free(shell);
}
