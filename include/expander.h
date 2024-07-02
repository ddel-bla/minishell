/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddel-bla <ddel-bla@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:53:47 by claferna          #+#    #+#             */
/*   Updated: 2024/07/02 18:30:28 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// ......... FUNCTIONS ..........
// ___________ command __________
void	expander(t_env *env, t_cmd *cmd, t_cmd **exp);
t_cmd	*copy_cmd(t_cmd *original);
char	*expand_quotes(t_env *list, char *cmd);

#endif
