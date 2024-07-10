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

#include "../../../include/minishell.h"

static char	*process_here_doc(t_redir *hd_redir);

/*
 * Initiliaze aux structure.
 */
void	init_aux2(t_aux_exp *aux)
{
	aux->out_index = 0;
	aux->s_quotes = 0;
	aux->i = 0;
}

/*
 * Calls the trim_quotes function in order to trim the arguments 
 * of a command.
 */
void	process_cmd_arg(t_cmd *cmd)
{
	t_cmd	*c_aux;
	char	*processed;
	int		i;

	i = 0;
	c_aux = cmd;
	while (c_aux->cmd[i])
	{
		processed = ft_trim_quotes(c_aux->cmd[i]);
		free(c_aux->cmd[i]);
		c_aux->cmd[i] = NULL;
		c_aux->cmd[i++] = processed;
	}
}

void	process_cmd_redir(t_redir *redir)
{
	t_redir	*re_aux;
	char	*processed;

	re_aux = redir;
	while (re_aux != NULL)
	{
		if (contains_space(re_aux->file) && re_aux->type != T_RED_HER)
			processed = ft_strdup(re_aux->file);
		else if (re_aux->type == T_RED_HER)
			processed = process_here_doc(re_aux);
		else
			processed = ft_trim_quotes(re_aux->file);
		free(re_aux->file);
		re_aux->file = processed;
		re_aux = re_aux->next;
	}
}

static char	*process_here_doc(t_redir *hd_redir)
{
	char	*processed;

	if (contains_quote(hd_redir->file))
	{
		processed = ft_trim_quotes(hd_redir->file);
		return (processed);
	}
	else
		hd_redir->type = T_RED_HER_EX;
	return (ft_strdup(hd_redir->file));
}
