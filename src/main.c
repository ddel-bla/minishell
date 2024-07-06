/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:18:35 by claferna          #+#    #+#             */
/*   Updated: 2024/07/04 17:14:25 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	start_minishell(char **envp);
int		process(t_shell *shell, char *input);

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 && argv[1])
		return (1);
	print_header();
	start_minishell(envp);
	return (0);
}

/*
 * Starts the minishell: while loop reading commands
 */
void	start_minishell(char **envp)
{
	char	*input;
	t_shell	*shell;

	shell = init(envp);
	while (1)
	{
		input = readline(PROMPT);
		if (*input)
		{
			add_history(input);
			process(shell, input);
		}
	}
	free_env_and_shell(shell);
}

/*
 * Executes the process of processing a command (lexer, parser, executor).
 */
int	process(t_shell *shell, char *input)
{
	if (lexer(input, &shell->token))
	{
		print_error("minishell: syntax error");
		free_lexer_err(shell, input);
		return (1);
	}
	//print_tokens(shell->token);//DEBUG
	parser(&shell->token, &shell->cmd);
	//print_cmd(shell->cmd);//DEBUG
	expander(&shell->env, shell->cmd);
	//print_cmd(shell->exp);//DEBUG
	exec_builtin(shell, shell->cmd);
	//executer(shell);
	free_loop(shell, input);
	return (0);
}
