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
 * Checks if a string contains a quote
 */
int	contains_quote(const char *str)
{
	while (*str)
	{
		if (ft_isquote((unsigned char)*str))
			return (1);
		str++;
	}
	return (0);
}

/*
 * Removes all the quotes (double/simple) in a string.
 */
char	*remove_quotes(const char *str)
{
	int		length;
	char	*result;
	int		j;
	int		i;

	length = ft_strlen(str);
	result = (char *)malloc(length + 1);
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (i < length)
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
