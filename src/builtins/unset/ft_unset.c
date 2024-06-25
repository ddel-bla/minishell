#include "../../../include/minishell.h"

/*
 * Deletes an environment variable.
 */
void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	char	*arg;
	int		i;

	i = 1;
	while (cmd->cmd[i])
	{
		arg = cmd->cmd[i];
		delete_env_by_name(shell->env, arg);
		i++;
	}
	shell->exit_status = 0;
}
