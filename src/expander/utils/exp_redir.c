/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:56:02 by ddel-bla          #+#    #+#             */
/*   Updated: 2024/07/15 18:56:09 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	red_her(t_shell *shell, char *limiter, int mode)
{
	char	*line;
	char	*check;
	int		fd;
	char	*parsed;

	check = ft_strjoin(limiter, "\n");
	fd = ft_open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || (!ft_strncmp(line, check, ft_strlen(line))))
			break ;
			
		fprintf(stderr, "Print '%i'\n", mode);
		if (!mode)
			write(fd, line, ft_strlen(line));
		else
		{	
			line = dquote(line, shell, &parsed);
			write(fd, parsed, ft_strlen(line));
		}
		free(line);
	}
	free(line);
	free(check);
	close(fd);
}

void	check_redir(t_shell *shell, t_cmd *exp)
{
	t_redir	*act;

	act = exp->redirection;
	while (act)
	{
		if (act->type == T_RED_HER )
			red_her(shell, act->file, 0);
		else if (act->type == T_RED_HER_EX)
			red_her(shell, act->file, 1);
		act = act->next;
	}
}
