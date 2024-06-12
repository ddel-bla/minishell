/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:30:14 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/06/12 10:38:36 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_quotes(char *string) 
{
	char *src = string, *dst = string;
	while (*src)
    {
        
    	if (' ' != ((unsigned char)*src))
			*dst++ = *src;
        src++;
    }
	*dst = '\0';
    return (dst);
}
