# include "../../include/minishell.h"

/*
 * Checks whether the executed command is one of the built-ins
 * methods and executes it.
 */
void	exec_builtin(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmd;
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ft_export(shell);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		ft_unset(shell);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ft_exit(shell);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ft_cd(shell);
}
