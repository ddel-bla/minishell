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

/*
 * Trims quotes, removes quoes (simple/double) from beginning and end 
 * of a string.
 */
char	*ft_trim_quotes(char *str)
{
	char	*result;
	int		j;
	int		i;
	char	quote;
	int		start;

	result = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote = str[i++];
			start = i;
			while (str[i] && str[i++] != quote)
				i++;	
			if (str[i] == quote)
				i++;
			while (start < i - 1)
				result[j++] = str[start++];
		}
		else
			result[j++] = str[i++];
	}
	return (result);
}

/*
 * Copies n length of a string into another.
 */
void	ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[n] = '\0';
}
