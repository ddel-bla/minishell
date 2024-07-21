/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:22:14 by claferna          #+#    #+#             */
/*   Updated: 2024/07/15 14:00:14 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ........... MACROS ...........
// __________ visuals ___________
# define PROMPT "minishell>$"
# define COLORED_PROMPT "\033[1;36mminishell>$\033[1;37m"

// ............ LIBS ............
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <sys/ioctl.h>

// .......... HEADERS ...........
# include "../lib/libft/libft.h"
# include "./env.h"
# include "./lexer.h"
# include "./parser.h"
# include "./expander.h"
# include "./executer.h"
# include "./signals.h"

// ...... GLOBAL VARIBALE .......
extern int	g_signal;

// .......... STRUCTS ...........
typedef struct s_shell
{
	t_token		*token;
	t_cmd		*cmd;
	t_cmd		*exp;
	t_env		*env;
	int			exit_status;
	char		**envp;
	t_pid_node	*pid_list;
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
void	expander(t_shell *shell, t_cmd *cmd);
// ____________ executer ________
void	executer(t_shell *shell);
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
int		validate_syntax(char *argv);
// ____________ signals _________
void	signal_init(void);
void	handle_ctrl_d(char *input);
// ____________ prints __________
void	print_header(void);
void	print_header_nc(void);
void	print_error(char *str);
char	*select_prompt(int is_colored);
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
int		contains_quote(const char *str);
char	*remove_quotes(const char *str);
int		ft_only_spaces(char *input);
int		ft_fork(void);
int		ft_open(char *file, int mode, int flag);
void	ft_pipe(int *fds);
int		is_builtin(char *cmd);
char	*ft_trim_quotes(char *str);
int		contains_space(const char *str);
void	ft_strncpy(char *dest, char *src, int n);
int		ft_only_spaces(char *input);
#endif
