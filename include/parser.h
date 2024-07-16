/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/06/18 16:55:08 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// .......... STRUCTS ...........
// -------- REDIRECTION ---------
typedef struct s_redirection
{
	int						type;
	char					*file;
	struct s_redirection	*next;
}							t_redir;
// ---------- COMMAND -----------
typedef struct s_command
{
	char					**cmd;
	int						operator_type;
	struct s_redirection	*redirection;
	struct s_command		*next;
}							t_cmd;

// ......... FUNCTIONS ..........
// ___________ command __________
t_cmd	*create_cmd(char **cmd, int operator_type, t_redir *redir);
void	add_cmd(t_cmd **list, t_cmd *cmd);
t_cmd	*get_cmd_by_index(t_cmd *list, int index);
int		cmd_size(t_cmd *list);
void	print_cmd(t_cmd *list);
void	free_cmd(t_cmd *list);
// ____________ redirs ___________
t_redir	*create_redir(int type, char *file);
void	add_redir(t_redir **list, t_redir *redir);
t_redir	*get_redir_by_index(t_redir *list, int index);
int		redirs_size(t_redir *list);
void	print_redirs(t_redir *list);
void	free_redirs(t_redir *list);
// ___________ utils _____________
char	**add_to_args(char **args, t_token **tokens);
#endif
