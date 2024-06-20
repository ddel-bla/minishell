#include "../../../include/minishell.h"

void	ft_unset(t_shell *shell)
{
	t_cmd	*cmd;
	int	i;
	
	cmd = shell->cmd;
	while (cmd->cmd[i])
	{
		delete_env_by_name(shell->env, cmd->cmd[i]);
		i++;
	}	
}
