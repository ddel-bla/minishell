/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:06:49 by claferna          #+#    #+#             */
/*   Updated: 2024/07/02 18:47:33 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int			validate_syntax(char *arg);
static void	without_args(t_env *env);
static void	print_stderror(char *str);

/*
 * Reproduces the behaviour of the 'export' function.
 */
void	ft_export(t_shell *shell, t_cmd	*cmd)
{
	int	i;

	i = 0;
	if (count_args(cmd) == 1)
		without_args(shell->env);
	else
	{
		while (cmd->cmd[++i])
		{
			if (validate_syntax(cmd->cmd[i]))
				add_exported_env(&shell->env, cmd->cmd[i]);
			else
				shell->exit_status = 1;
		}
	}
	shell->exit_status = 0;
}

/*
 * Executes 'export' with no commands (sorts and prints env variables)
 */
static void	without_args(t_env *env)
{
	t_env	*sorted_list;
	t_env	*aux;

	sorted_list = copy_list(env);
	if (sorted_list)
	{
		sort_env_list(&sorted_list);
		aux = sorted_list;
		while (aux)
		{
			if (aux->value == NULL)
				printf("declare -x %s\n", aux->name);
			else if (ft_strcmp(aux->name, "_") == 0)
				(void)aux->value;
			else
				printf("declare -x %s=%s\n", aux->name, aux->value);
			aux = aux->next;
		}
	}
	free_env(sorted_list);
}

/*
 * Validate the syntax of the given command.
 */
int	validate_syntax(char *arg)
{
	char	*name;
	int		i;

	i = 0;
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (!arg[i])
		return (0);
	if (arg[i] != '=' || arg[0] == '=')
		return (print_stderror(arg), 0);
	if (ft_strchr(arg, '='))
	{
		i = 0;
		while (arg[i])
			if (arg[i++] == '=')
				break ;
		name = ft_substr(arg, 0, i - 2);
		if (ft_isdigit(name[0]))
			return (print_stderror(arg), free(name), 0);
		return (free(name), 1);
	}
	return (0);
}

/*
 * Print messages in stderror
*/
static void	print_stderror(char *str)
{
	ft_putstr_fd("\033[1;31mexport: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" invalid identifier\033[0m", 2);
}
