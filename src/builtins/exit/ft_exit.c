#include "../../../include/minishell.h"

static int	validate_exit(t_cmd *cmd);

/*
 * Replicates the behaviour of the exit command.
 */
void	ft_exit(t_shell *shell, t_cmd	*cmd)
{
	shell->exit_status = validate_exit(cmd);
	if (shell->exit_status != 1 && shell->exit_status != 2)
	{
		if (cmd->cmd[1])
			shell->exit_status = ft_atoi(cmd->cmd[1]);
		exit(shell->exit_status);
	}
}

/*
 * Validates the input of the exit command.
 */
static int	validate_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (count_args(cmd) > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (count_args(cmd) == 1)
		return (0);
	if (cmd->cmd[1])
	{
		while (cmd->cmd[1][i])
		{
			if (!ft_isdigit(cmd->cmd[1][i]))
			{
				ft_putstr_fd("exit: a numeric argument", 2);
				ft_putendl_fd("is required", 2);
				return (2);
			}
			i++;
		}
		return (0);
	}
	return (0);
}
