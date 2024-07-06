/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:08 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/03 15:30:33 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_cmd_args(t_cmd *cmd, t_env *env);
static void	expand_redir_file(t_cmd *cmd, t_env *env);

/*
 * Process of expanding all commands and redirections, excluding here_doc 
 * redirections.
 */
void	expander(t_env **env, t_cmd *cmd)
{
	t_cmd	*current;
	t_env	*en_vars;

	current = cmd;
	en_vars = *env;
	while (current != NULL)
	{
		expand_cmd_args(current, en_vars);
		expand_redir_file(current, en_vars);
		current = current->next;
	}
}

/*
 * Process of expanding each argument of each command.
 */
static void	expand_cmd_args(t_cmd *cmd, t_env *env)
{
	int		expanded_size;
	char	*expanded;
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		expanded_size = calculate_expanded_size(cmd->cmd[i], env);
		expanded = (char *)malloc(sizeof(char) * expanded_size);
		if (!expanded)
			exit(EXIT_FAILURE);
		expand(cmd->cmd[i], expanded, env);
		free(cmd->cmd[i]);
		cmd->cmd[i] = NULL;
		cmd->cmd[i] = expanded;
		i++;
	}
}

/*
 * Process of expanding each redirection file (in/outfile) excluding 
 * here_doc limiters.
 */
static void	expand_redir_file(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		expanded_size;
	char	*expanded;

	redir = cmd->redirection;
	while (redir != NULL)
	{
		if (redir->type != T_RED_HER)
		{
			expanded_size = calculate_expanded_size(redir->file, env);
			expanded = (char *)malloc(sizeof(char) * expanded_size);
			if (expanded == NULL)
				exit(EXIT_FAILURE);
			expand(redir->file, expanded, env);
			redir->file = NULL;
			redir->file = expanded;
		}
		redir = redir->next;
	}
}
