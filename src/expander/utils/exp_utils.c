/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:06:05 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/24 16:37:53 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_add_var(char *line, char *var)
{
	char	*new;

	new = ft_strjoin(line, var);
	free(line);
	return (new);
}

char	*ft_add(char *line, int len, char **new)
{
	char	*add;
	char	*aux;

	add = ft_substr(line, 0, len);
	aux = ft_strjoin(*new, add);
	free(add);
	free(*new);
	*new = aux;
	return (line + len + 1);
}
