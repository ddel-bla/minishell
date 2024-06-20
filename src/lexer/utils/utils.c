/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:19:27 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 18:39:53 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
 * Compares two strings.
 */
/*
int	ft_strcmp(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i] == c[i] && c[i] && str[i])
		i++;
	return (str[i] - c[i]);
}
*/
/*
 * Calculates the length of a given string.
 *//*
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
*/
/*
 * Substract part of a given string
 */
char	*ft_substr(char *str, int start, int end)
{
	int	len;
	int	i;
	char	*aux;

	if (start > end || start < 0 || end > ft_strlen(str))
		return (NULL);
	len = end - start + 1;
	aux = (char *)malloc(sizeof(char) * len + 1);
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
 * Checks whether a character is a quote (double/simple)
 */
int	ft_isquote(char c)
{
	return (c == '\'' || c == '\"');
}

/*
 * Check whether a character is a special character ('|', '<', '>').
 */
int	ft_isspecial(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/*
 * Eliminates the leading spaces.
 */
char	*ft_trim_leading_spaces(char *str)
{
	while (ft_isspace((unsigned char)*str))
		str++;
	return str;
}

/*
 * Eliminites the trailing spaces.
 */
void	ft_trim_trailing_spaces(char *str)
{
	char *end;
       
	end = str + ft_strlen(str) - 1;
	while(end > str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
}

/*
 * Eliminates both, leading and trailing spaces.
 */
char	*ft_trim_spaces(char *str)
{
	char *trimmed_str;
	
	trimmed_str = ft_trim_leading_spaces(str);
	ft_trim_trailing_spaces(trimmed_str);
	return (trimmed_str);
}
