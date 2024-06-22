#include "../../../include/minishell.h"

void	ft_echo(t_shell *shell)
{
	t_cmd	*cmd;
	int	i;

	cmd = shell->cmd;
	i = 1;
	if (cmd->cmd[1] && ft_strcmp(cmd->cmd[1], "-n") == 0)
		i++;
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i++], 1); //cambiar a fd redireccion
		if (cmd->cmd[i])
			ft_putchar_fd(' ',  1);	//cambiar a fd redirección
	}
	if (cmd->cmd[1] && !ft_strcmp(cmd->cmd[1], "-n") == 0 \
			|| count_args(shell) == 1)
		ft_putchar_fd('\n', 1);	//cambair redirección
	shell->exit_status = 0;
}
