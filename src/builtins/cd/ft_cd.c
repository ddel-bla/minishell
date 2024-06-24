#include "../../../include/minishell.h"

static void change_env_oldpwd(t_shell *shell);
static char *get_path(t_shell *shell, char *cmd);
static void change_env_pwd(t_shell *shell);

/*
 * Recreates the behaviour of the cd command.
 */
void    ft_cd(t_shell *shell, t_cmd	*cmd)
{
    char    *new_path;

    if (count_args(cmd) > 2)
    {
        ft_putendl_fd("cd: too many arguments", 2);
        shell->exit_status = 1;
        return ;
    }
    shell->exit_status = 0;
    new_path = get_path(shell, cmd->cmd[1]);
    if (new_path == NULL)
        return ;
    if (!access(new_path, 0))
        change_env_oldpwd(shell);
    if (chdir(new_path))
    {
        perror("cd");
        shell->exit_status = 1;
        free(new_path);
        return ;
    }
    free(new_path);
    change_env_pwd(shell);
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

static char *get_path(t_shell *shell, char *cmd)
{
    char    *new_path;
    char    *real_path;

    if (getenv("HOME") && (!cmd || !ft_strcmp(cmd, "~") || !ft_strcmp(cmd, "--") \
            || !ft_strcmp(cmd, "~/")))
        new_path = ft_strdup(getenv("HOME"));
    else if (getenv("HOME") && !ft_strncmp(cmd, "~/", 2))
    {
        real_path = ft_substr(cmd, 1, ft_strlen(cmd));
        new_path = ft_strjoin(getenv("HOME"), real_path);
        free(real_path);
    }
    else if (!getenv("HOME"))
    {
        ft_putendl_fd("cd: HOME is not set", 2);
        shell->exit_status = 1;
        return (NULL);
    }
    else if (cmd)
        new_path = ft_strdup(cmd);
    else
        new_path = ft_strdup("");
    return (new_path);
}

static void change_env_pwd(t_shell *shell)
{
    char    *pwd;
    char    *name;

    pwd = getcwd(NULL, 0);
    name = ft_strjoin("PWD=", pwd);
    add_exported_env(&shell->env, name);
    free(pwd);
    free(name);
}