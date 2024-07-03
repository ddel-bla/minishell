/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:10:39 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:10:40 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Substract part of a given string
 */
char	*ft_substr(char *str, int start, int end)
{
	int		len;
	int		i;
	char	*aux;

	if (start > end || start < 0 || end > ft_strlen(str))
		return (NULL);
	len = end - start + 1;
	aux = (char *)malloc(sizeof(char) * (len + 1));
	if (!aux)
		return (NULL);
	i = 0;
	while (start <= end)
		aux[i++] = str[start++];
	aux[i] = '\0';
	return (aux);
}

/*
 * Checks wether a character is a space.
 */
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' \
			|| c == '\f');
}
