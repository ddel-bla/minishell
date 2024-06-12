#include "../../../include/minishell.h"

int	ft_strcmp(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i] == c[i] && c[i] && str[i])
		i++;
	return (str[i] - c[i]);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
char	*ft_substr(char *input, int start, int end)
{
	int	len;
	int	i;
	char	*aux;

	if (start > end || start < 0 || end >= ft_strlen(input))
		return (NULL);
	len = end - start + 1;
	aux = (char *)malloc(sizeof(char) * len + 1);
	if (!aux)
		return (NULL);
	i = 0;
	while (start <= end)
		aux[i++] = input[start++];
	aux[i] = '\0';
	return (aux);
}
