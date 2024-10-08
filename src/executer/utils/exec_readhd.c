/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_readhd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:33:29 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/09/12 19:54:47 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*here_expand(char *line, t_shell *shell)
{
	char	*new;
	int		i;
	char	*tmp;

	new = ft_strdup("");
	tmp = line;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			line = dollar(line, shell, &new);
		else
		{
			while (line[i] != '\0' && line[i] != '\n' && line[i] != '$')
				i++;
			line = ft_add(line, i - 1, &new);
		}
		i = 0;
	}
	free(tmp);
	return (new);
}

void	ft_here_docs(t_shell *shell, t_redir *red)
{
	char	*line;
	int		fd;

	fd = ft_open(red->heredoc_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while (line && ft_strncmp(line, red->file, ft_strlen(red->file) + 1))
	{
		if (g_signal == SIGINT)
		{
			free(line);
			close(fd);
			shell_cleanup_here_docs(shell);
			return ;
		}
		if (red->type == T_RED_HER_EX)
			line = here_expand(line, shell);
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
}

static void	ft_add_prefix(char **hd, t_env *env)
{
	t_env	*myenv;
	char	*aux;
	char	*under;

	myenv = get_env_by_name(env, "SYSTEMD_EXEC_PID");
	if (!myenv || !myenv->value)
		return ;
	under = ft_strjoin("_", myenv->value);
	aux = ft_strjoin(*hd, under);
	free(under);
	free(*hd);
	*hd = aux;
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
		while (red != NULL && g_signal != SIGINT)
		{
			if (red->type == T_RED_HER || red->type == T_RED_HER_EX)
			{
				shell->n_hdcs++;
				hd_number = ft_itoa(shell->n_hdcs);
				red->heredoc_file = ft_strjoin("./tmp_", hd_number);
				ft_add_prefix(&red->heredoc_file, shell->env);
				free(hd_number);
				ft_here_docs(shell, red);
			}
			red = red->next;
		}
		current = current->next;
	}
}
