/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:05:34 by claferna          #+#    #+#             */
/*   Updated: 2024/06/28 16:05:35 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	change_env_path(t_shell *shell, char *var, int *error);
static char	*get_path(t_shell *shell, char *cmd);

/*
 * Reproduces the behaviour of the cd command.
 */
void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*new_path;
	int		error;

	error = 0;
	if (count_args(cmd) > 2)
	{
		print_error("cd: too many arguments");
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
	new_path = get_path(shell, cmd->cmd[1]);
	if (new_path == NULL)
		return ;
	if (access(new_path, 0) != -1)
		change_env_path(shell, "OLDPWD=", &error);
	if (chdir(new_path))
	{
		perror("\033[1;31mcd\033[0m");
		shell->exit_status = 1;
		free(new_path);
		return ;
	}
	free(new_path);
	change_env_path(shell, "PWD=", &error);
}

/*
 * Changes the OLDPWD env variable to the current path, that will become
 * the old one.
 */
static void	change_env_path(t_shell *shell, char *var, int *error)
{
	char	*pwd;
	char	*name;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (*error == 0)
		{
			perror("getcwd");
			*error = 1;
		}
		return ;
	}
	name = ft_strjoin(var, pwd);
	add_exported_env(&shell->env, name);
	free(pwd);
	free(name);
}

/*
 * Returns the path executed by the cd command.
 */
static char	*get_path(t_shell *shell, char *cmd)
{
	char	*new_path;
	char	*real_path;

	if (get_env_value(shell->env, "HOME") && (!cmd || !ft_strcmp(cmd, "~") \
		|| !ft_strcmp(cmd, "--") || !ft_strcmp(cmd, "~/")))
		new_path = ft_strdup(get_env_value(shell->env, "HOME"));
	else if (get_env_value(shell->env, "HOME") && !ft_strncmp(cmd, "~/", 2))
	{
		real_path = ft_substr(cmd, 1, ft_strlen(cmd));
		new_path = ft_strjoin(get_env_value(shell->env, "HOME"), real_path);
		free(real_path);
	}
	else if (cmd)
		new_path = ft_strdup(cmd);
	else if (!get_env_value(shell->env, "HOME"))
	{
		print_error("cd: HOME is not set");
		shell->exit_status = 1;
		return (NULL);
	}
	else
		new_path = ft_strdup("");
	return (new_path);
}
