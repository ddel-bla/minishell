/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:56:02 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/16 15:18:06 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*exp_dollar(char *cmd, t_shell *shell, char **new)
{
	char	*var_name;
	t_env	*myenv;
	char	*aux;
	int		i;

	i = 1;
	if (cmd[i] == '?')
		return (ft_status(cmd, shell, new));
	while (cmd[i] != ' ' && cmd[i] != '$' && cmd[i] != '\''
		&& cmd[i] != '\"' && cmd[i] != '\0')
		i++;
	fprintf(stderr, "dollar '%i'\n", i);
	if (i == 1)
		return (cmd + 2);
	var_name = ft_substr(cmd, 1, i - 1);
	fprintf(stderr,"var  = '%s'", var_name);
	myenv = get_env_by_name(shell->env, var_name);
	free(var_name);
	if (myenv)
	{
		aux = ft_strjoin(*new, myenv->value);
		fprintf(stderr,"aux  = '%s'", myenv->value);
		free(*new);
		*new = aux;
	}
	return (cmd + i);
}

char	*check_expand(char *line, t_shell *shell, int mode)
{
	char	*new;
	char	*add;
	char	*aux;
	int		i;
	
	//if (!mode) Sustituir cuando se cambie el lexer
	new = ft_strdup("");
	if (new == NULL)
		return (NULL);
	if (mode)
		return (line);
	i = 0;
	fprintf(stderr, "line '%s'", line);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '$')
			line = exp_dollar(line, shell, &new);
		while (line[i] != '\0' && line[i] != '\n' && line[i] != '$')
			i++;
		fprintf(stderr,"i = '%d'\n", i);
		if (i != 2)
		{
			add = ft_substr(line, 0, i);
			fprintf(stderr,"add  = '%s'", add);
			aux = ft_strjoin(new, add);
			fprintf(stderr,"aux  = '%s'", aux);
			free(new);
			free(add);
			new = aux;
		}
		line += i;
		i = 1;
	}
	fprintf(stderr,"FIN");
	return (new);
}
/*
void	red_her(int fds[2], t_shell *shell, char *limiter, int mode)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(line)) && line)
			break ;
		line = check_expand(line, shell, mode);
		fprintf(stderr, "Str: '%s'", line);
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}
*/

void	red_her(t_shell *shell, char *limiter, int mode)
{
	char	*line;
	int		fd;

	fd = ft_open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fprintf(stderr, "Print '%i'\n", mode);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || (!ft_strncmp(line, limiter, ft_strlen(line))))
			break ;
		line = check_expand(line, shell, mode);
		fprintf(stderr, "line  '%s'", line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}

void	check_redir(t_shell *shell, t_cmd *exp)
{
	t_redir	*act;
	char	*check;

	act = exp->redirection;
	check = ft_strjoin(act->file, "\n");
	while (act)
	{
		if (act->type == T_RED_HER)
			red_her(shell, check, 0);
		else if (act->type == T_RED_HER_EX)
			red_her(shell, check, 1);
		act = act->next;
	}
	free(check);
}
