/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:22:14 by claferna          #+#    #+#             */
/*   Updated: 2024/06/30 21:51:50 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ........... MACROS ...........
// __________ visuals ___________
# define PROMPT "\033[1;36mminishell>$\033[1;37m"
// _________ TOKEN_TYPE _________
# define T_END		-1
# define T_PIPE         0
# define T_RED_IN       1
# define T_RED_OUT      2
# define T_RED_APP      3
# define T_RED_HER      4
# define T_OTHER        5
# define T_LIMIT	6
# define T_OUTFILE	7
# define T_INFILE	8
# define T_COMMAND	9

// ............ LIBS ............
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// .......... HEADERS ...........
# include "./lexer.h"
# include "./parser.h"
# include "./env.h"
# include "./expander.h"
# include "../lib/libft/libft.h"
// .......... STRUCTS ...........

typedef struct s_shell
{
	t_token	*token;
	t_cmd	*cmd;
	t_cmd	*exp;
	t_env	*env;
	int		exit_status;
}			t_shell;

// ......... FUNCTIONS ..........
// ___________ lexer ____________
int		lexer(char *input, t_token **token_list);
int		get_basic_type(char *token);
void	get_definitive_type(t_token **token_list);
char	*get_str_types(int type);
int		validate_token(char *token);
int		check_syntax(t_token **tokens);
// ____________ parser __________
void	parser(t_token **tokens, t_cmd **cmd);
// ____________ expander ________
void	expander(t_env *env, t_cmd *cmd, t_cmd **exp);
// __________ built-ins _________
void	exec_builtin(t_shell *shell, t_cmd *cmd);
void	ft_env(t_shell	*shell, t_cmd *cmd);
void	ft_unset(t_shell *shell, t_cmd *cmd);
void	ft_export(t_shell *shell, t_cmd *cmd);
void	ft_pwd(t_shell *shell, t_cmd *cmd);
void	ft_echo(t_shell *shell, t_cmd *cmd);
void	ft_exit(t_shell *shell, t_cmd *cmd);
void	ft_cd(t_shell *shell, t_cmd *cmd);
int		count_args(t_cmd *cmd);
// ____________ prints __________
void	print_header(void);
void	print_error(char *str);
// __________ main-utils ________
t_shell	*init(char **envp);
void	free_env_and_shell(t_shell *shell);
void	free_loop(t_shell *shell, char *input);
void	free_lexer_err(t_shell *shell, char *input);
// ____________ utils ___________
int		ft_strcmp(char *str, char *c);
char	*ft_substr(char *input, int start, int end);
int		ft_isspace(char c);
int		ft_isquote(char c);
int		ft_isspecial(char c);
char	*ft_trim_spaces(char *str);
#endif
