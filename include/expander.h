/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/24 16:47:49 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
// .......... STRUCTS ...........

typedef struct s_shell	t_shell;

// ......... FUNCTIONS ..........
t_cmd	*copy_cmd(t_cmd *original);
char	*expand_quotes(t_shell *shell, char *cmd);

int		ft_out_process(char *outfile, char *cmd, char **envp, int mode);

char	*ft_status(char *cmd, t_shell *shell, char **new);
char	*dollar(char *cmd, t_shell *shell, char **new);
char	*quote(char *cmd, char **new);
char	*dquote(char *cmd, t_shell *shell, char **new);
char	*squote(char *cmd, char **new);

char	*ft_add_var(char *line, char *var);
char	*ft_add(char *line, int len, char **new);
#endif
