#include "../../../include/minishell.h"

static int	validate_syntax(char *arg);
static int  without_args(t_env *env);

void	ft_export(t_shell *shell, t_cmd	*cmd)
{
	int	i;

	i = 0;
	if (count_args(cmd) == 1)
		without_args(shell->env); //cambiar
	else
	{
		while(cmd->cmd[++i])
		{
			if (validate_syntax(cmd->cmd[i]))
				add_exported_env(&shell->env, cmd->cmd[i]);
			else
				shell->exit_status = 1;
		}
	}
	shell->exit_status = 0;
}

static int  without_args(t_env *env)
{
	t_env	*sorted;

	sorted = copy_list(env);
	sort_list(sorted);
	while (sorted)
	{
		if (sorted->value == NULL)
			printf("declare -x %s\n", sorted->name);
		else if(ft_strcmp(sorted->name, "_") == 0)
			printf("declare -x\n");
		else
			printf("declare -x %s=%s\n", sorted->name, sorted->value);
		sorted = sorted->next;
	}
	free_env(sorted);
}

static int	validate_syntax(char *arg)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	if (ft_strchr(arg, '='))
	{
		while (arg[i])
			if (arg[i++] == '=')
				break ;	
		name = ft_substr(arg, 0, i - 2);
		value = ft_substr(arg, i, ft_strlen(arg) - 1);
	}
	return (0);
}
