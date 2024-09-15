/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:18:35 by claferna          #+#    #+#             */
/*   Updated: 2024/09/15 14:58:38 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	start_minishell(char **envp, int color);
int		process(t_shell *shell, char *input);

int	main(int argc, char **argv, char **envp)
{
	if (argc > 2 && argv[2])
		return (1);
	if (argv[1])
		print_header();
	else
		print_header_nc();
	start_minishell(envp, argc);
	return (0);
}

/*
 * Starts the minishell: while loop reading commands
 */
void	start_minishell(char **envp, int color)
{
	char	*input;
	t_shell	*shell;

	shell = init(envp);
	while (1)
	{
		signals_terminal();
		input = readline(select_prompt(color));
		if (!input)
		{
			printf("exit\n");
			exit(shell->exit_status);
		}
		if (g_signal)
			shell->exit_status = 128 + g_signal;
		if (!ft_only_spaces(input))
			process(shell, input);
		else
			free(input);
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
		add_history(input);
		print_error("minishell: syntax error");
		free_lexer_err(shell, input);
		return (1);
	}
	parser(&shell->token, &shell->cmd);
	expander(shell, &shell->exp);
	executer(shell);
	if (shell->exit_status == 0)
		add_history(input);
	free_loop(shell, input);
	return (0);
}
