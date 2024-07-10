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

static void	expand_cmd_args(t_cmd *cmd, t_shell *shell);
static void	expand_redir_file(t_cmd *cmd, t_shell *shell);
static void	post_process(t_cmd *cmd);

/*
 * Process of expanding all commands and redirections, excluding here_doc 
 * redirections.
 */
void	expander(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current != NULL)
	{
		expand_cmd_args(current, shell);
		expand_redir_file(current, shell);
		post_process(current);
		current = current->next;
	}
}

/*
 * Process of expanding each argument of each command.
 */
static void	expand_cmd_args(t_cmd *cmd, t_shell *shell)
{
	int		expanded_size;
	char	*expanded;
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		expanded_size = calculate_expanded_size(cmd->cmd[i], shell);
		expanded = (char *)malloc(sizeof(char) * expanded_size);
		if (!expanded)
			exit(EXIT_FAILURE);
		expand(cmd->cmd[i], expanded, shell);
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
static void	expand_redir_file(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		expanded_size;
	char	*expanded;

	redir = cmd->redirection;
	while (redir != NULL)
	{
		if (redir->type != T_RED_HER)
		{
			expanded_size = calculate_expanded_size(redir->file, shell);
			expanded = (char *)malloc(sizeof(char) * expanded_size);
			if (expanded == NULL)
				exit(EXIT_FAILURE);
			expand(redir->file, expanded, shell);
			redir->file = NULL;
			redir->file = expanded;
		}
		else
			redir->file = ft_strdup(redir->file);
		redir = redir->next;
	}
}

/*
 * Deleting all quotes from the commands 
 */
static void	post_process(t_cmd *cmd)
{
	t_cmd	*c_aux;

	c_aux = cmd;
	process_cmd_arg(c_aux);
	process_cmd_redir(c_aux->redirection);
}
