#include "../../../include/minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1); //cambiar fd de salida
	free(pwd);
	shell->exit_status = 0;
}
