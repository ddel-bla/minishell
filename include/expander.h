/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/03 15:29:42 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// .......... STRUCTS ...........
typedef struct s_shell	t_shell;
// _________ s_aux_exp _________
typedef struct s_aux_exp
{
	int	out_index;
	int	s_quotes;
	int	d_quotes;
	int	i;
}		t_aux_exp;

// ......... FUNCTIONS ..........
// ___________ main __________
int		calculate_expanded_size(char *input, t_shell *shell);
void	expand(char *input, char *output, t_shell *shell);
// ___________ utils __________
void	variable_expansion(char *input, char *output, t_aux_exp *aux, \
	t_env *env);
void	count_env_var(char *input, int *index, int *length, t_env *env);
void	insert_dollar(char *output, int *out_index, int *index);
void	count_vars(int *i, int *size);
void	init_aux(t_aux_exp *aux);
void	init_aux2(t_aux_exp *aux);
void	process_cmd_arg(t_cmd *cmd);
void	process_cmd_redir(t_redir *redir);
int		ft_contains_space(char *str);
void	treat_expansion(char *input, char *output, t_aux_exp *aux, \
	t_shell *shell);
void	count_expansion(char *input, t_aux_exp *aux, t_shell *shell);
#endif
