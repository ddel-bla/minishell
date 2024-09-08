/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_copycmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:01 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/08/16 08:43:12 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_redir	*copy_redir_node(t_redir *original)
{
	t_redir	*copy;

	copy = ft_malloc(sizeof(t_redir));
	copy->type = original->type;
	if (original->file)
	{
		copy->file = ft_strdup(original->file);
		if (copy->file == NULL)
		{
			free(copy);
			return (NULL);
		}
	}
	else
		copy->file = NULL;
	copy->heredoc_file = NULL;
	copy->next = NULL;
	return (copy);
}

t_redir	*copy_redirections(t_redir *original)
{
	t_redir	*copy;

	if (original == NULL)
		return (NULL);
	copy = copy_redir_node(original);
	if (copy == NULL)
		return (NULL);
	copy->next = copy_redirections(original->next);
	return (copy);
}

int	count_commands(char **cmd)
{
	int	count;

	count = 0;
	while (cmd && cmd[count])
		count++;
	return (count);
}

char	**copy_commands(char **original_cmd)
{
	char	**copy_cmd;
	int		count;
	int		i;
	int		j;

	count = count_commands(original_cmd);
	copy_cmd = ft_malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count)
	{
		copy_cmd[i] = ft_strdup(original_cmd[i]);
		if (copy_cmd[i] == NULL)
		{
			j = 0;
			while (j < i)
				free(copy_cmd[j++]);
			free(copy_cmd);
			return (NULL);
		}
		i++;
	}
	copy_cmd[count] = NULL;
	return (copy_cmd);
}

t_cmd	*copy_cmd(t_cmd *original)
{
	t_cmd	*copy;

	if (original == NULL)
		return (NULL);
	copy = ft_malloc(sizeof(t_cmd));
	copy->cmd = copy_commands(original->cmd);
	if (original->cmd && copy->cmd == NULL)
	{
		free(copy);
		return (NULL);
	}
	copy->operator_type = original->operator_type;
	copy->n_hds = original->n_hds;
	copy->redirection = copy_redirections(original->redirection);
	copy->next = copy_cmd(original->next);
	return (copy);
}
