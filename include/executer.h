/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/02 15:42:10 by ddel-bla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

// .......... STRUCTS ...........
// -------- REDIRECTION ---------


// ......... FUNCTIONS ..........
// ___________ command __________
void	ft_exec_proc(char **cmd, t_env *env, char **envp);
void	ft_exec_pipe(char **cmd, t_env *env, char **envp);
char	*ft_find_path(char *cmd, t_env *env);

#endif
