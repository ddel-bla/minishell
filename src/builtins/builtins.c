#include "../../include/minishell.h"

/*
 * Checks whether the executed command is one of the built-ins
 * methods and executes it.
 */
void	exec_builtin(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (!ft_strcmp(cmd->cmd[0], "env"))
		ft_env(shell);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return ;//ft_export(shell);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		ft_unset(shell);
}
