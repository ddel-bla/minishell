/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_readhd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:29 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/02 17:23:01 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*here_expand(char *line, t_shell *shell)
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
			line = ft_add(line, i - 1, &new);
		}
		i = 0;
	}
	return (new);
}

void	ft_here_docs(t_shell *shell, t_redir *red)
{
	char	*line;
	char	*aux;
	int		fd;

	g_signal = S_HEREDOC;
	fd = ft_open(red->heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || ((!ft_strncmp(line, red->file, ft_strlen(red->file))
					&& ft_strlen(red->file) == ft_strlen(line))))
			break ;
		// Habría que modificar varg[0] añadiendo line 
		// y después de acabar todos los heredoc hacer el add_history
		// if (line)
		// 	add_history(line);

		fprintf(stderr, "shell input = %s\n", shell->input);
		fprintf(stderr, "line = %s\n", line);
		aux = ft_strjoin(shell->input, line);
		fprintf(stderr, "aux = %s\n", aux);
		fprintf(stderr, "shell input = %s\n", shell->input);
		free(shell->input);
		shell->input = aux;
		fprintf(stderr, "shell input = %s\n", shell->input);
		if (red->type == T_RED_HER_EX)
			line = here_expand(line, shell);
		ft_putendl_fd(line, fd);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	g_signal = S_HEREDOC_END;
	close(fd);
}

void	ft_read_here_doc(t_shell *shell)
{
	char	*hd_number;
	t_cmd	*current;
	t_redir	*red;

	current = shell->exp;
	while (current != NULL)
	{
		red = current->redirection;
		while (red != NULL)
		{
			if (red->type == T_RED_HER || red->type == T_RED_HER_EX)
			{
				shell->n_hdcs++;
				hd_number = ft_itoa(shell->n_hdcs);
				red->heredoc_file = ft_strjoin("./build/tmp_", hd_number);
				free(hd_number);
				ft_here_docs(shell, red);
			}
			red = red->next;
		}
		current = current->next;
	}
}
