# include "../../include/minishell.h"

int	count_args(t_shell *shell)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = shell->cmd;
	while (cmd->cmd[i])
		i++;
	return (i);
}