/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:56:02 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/24 19:46:54 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*here_expand(char *line, t_shell *shell)
{
	char	*new;
	int		i;

	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			line = dollar(++line, shell, &new);
		else
		{
			while (line[i] != '\0' && line[i] != '\n' && line[i] != '$')
				i++;
			if (line[i] == '$')
				i--;
			line = ft_add(line, i, &new);
		}
		i = 0;
	}
	return (new);
}
