#include "../../../include/minishell.h"

/*
 * Reproduces the behaviour of the 'pwd' command.
 */
void	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	printf("%s", pwd);
	free(pwd);
	shell->exit_status = 0;
}
