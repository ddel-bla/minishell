# include "../../include/minishell.h"

int	count_args(t_cmd	*cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	return (i);
}