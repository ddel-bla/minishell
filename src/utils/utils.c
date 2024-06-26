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

#include "../../include/minishell.h"

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
	return (str);
}

/*
 * Eliminites the trailing spaces.
 */
void	ft_trim_trailing_spaces(char *str)
{
	char	*end;

	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
}

/*
 * Eliminates both, leading and trailing spaces.
 */
char	*ft_trim_spaces(char *str)
{
	char	*trimmed_str;

	trimmed_str = ft_trim_leading_spaces(str);
	ft_trim_trailing_spaces(trimmed_str);
	return (trimmed_str);
}
