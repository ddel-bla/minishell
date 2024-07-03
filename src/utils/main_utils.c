/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:10:21 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:10:22 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Initialiazes the shell struct.
 */
t_shell	*init(char **envp)
{
	t_shell	*shell;
	t_env	*env;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	env = NULL;
	shell->envp = envp;
	shell->token = NULL;
	shell->cmd = NULL;
	shell->exp = NULL;
	save_env(&env, envp);
	shell->env = env;
	shell->exit_status = 0;
	return (shell);
}

/*
 * Free env variables and the shell struct.
 */
void	free_env_and_shell(t_shell *shell)
{
	free_env(shell->env);
	free(shell);
}

/*
 * Frees all the elements once an interation in the main loop
 * has been completed.
 */
void	free_loop(t_shell *shell, char *input)
{
	if (shell->token)
		free_tokens(shell->token);
	shell->token = NULL;
	free_cmd(shell->cmd);
	free_cmd(shell->exp);
	shell->cmd = NULL;
	free(input);
}

/*
 * Frees the token struct and input when a lexer error ocurrs.
 */
void	free_lexer_err(t_shell *shell, char *input)
{
	if (shell->token)
		free_tokens(shell->token);
	shell->token = NULL;
	free(input);
}
