#include "../../../include/minishell.h"

static void change_env_oldpwd(t_shell *shell);


void    ft_cd(t_shell *shell)
{
    t_cmd   *cmd;
    char    *new_path;

    cmd = shell->cmd;
    if (count_args(shell) > 2)
        ft_putendl_fd("cd: too many arguments", 2);
    change_env_oldpwd(shell);
    if (!cmd->cmd[1] || ft_strcmp(cmd->cmd[1], "~") == 0 
        || ft_strcmp(cmd->cmd[1], "~/") == 0)
        new_path = ft_strdup(getenv("HOME"));
    else if (cmd->cmd[1])
        new_path = ft_strdup(cmd->cmd[1]);
    if (chdir(new_path))
        ft_putendl_fd("cd: error", 2);
    else
        ft_pwd(shell);
    free(new_path);
}

static void change_env_oldpwd(t_shell *shell)
{
    char    *pwd;
    char    *name;

    pwd = getcwd(NULL, 0);
    name = ft_strjoin("OLDPWD=", pwd);
    add_exported_env(&shell->env, name);
    free(pwd);
    free(name);
}