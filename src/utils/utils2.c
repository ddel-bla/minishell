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
	t_aux_exp	aux;
	char		*result;
	char		quote;
	int			start;

	init_aux2(&aux);
	result = (char *)ft_calloc(strlen(str) + 1, 1);
	while (str[aux.i])
	{
		if (ft_isquote(str[aux.i]))
		{
			quote = str[aux.i++];
			start = aux.i;
			while (str[aux.i] && str[aux.i] != quote)
				aux.i++;
			if (str[aux.i] == quote)
				aux.i++;
			while (start < aux.i - 1)
				result[aux.out_index++] = str[start++];
		}
		else
			result[aux.out_index++] = str[aux.i++];
	}
	return (result);
}

/*
 * Copies n length of a string into another.
 */
void	ft_strncpy(char *dest, char *src, int n)
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

/*
 * Checks whether a str contains a space
 */
int	contains_space(const char *str)
{
	while (*str)
	{
		if (ft_isspace((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}
