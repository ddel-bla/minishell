#include "../../../include/minishell.h"

static int	validate_syntax(char *arg);
static int	without_args(t_env *env);
static void	print_stderror(char *str);

/*
 * Reproduces the behaviour of the 'export' function.
 */
void	ft_export(t_shell *shell, t_cmd	*cmd)
{
	int	i;

	i = 0;
	if (count_args(cmd) == 1)
		without_args(shell->env);
	else
	{
		while (cmd->cmd[++i])
		{
			if (validate_syntax(cmd->cmd[i]))
				add_exported_env(&shell->env, cmd->cmd[i]);
			else
				shell->exit_status = 1;
		}
	}
	shell->exit_status = 0;
}

/*
 * Executes 'export' with no commands (sorts and prints env variables)
 */
static int	without_args(t_env *env)
{
	t_env	*sorted;

	sorted = copy_list(env);
	sort_list(sorted);
	while (sorted)
	{
		if (sorted->value == NULL)
			printf("declare -x %s\n", sorted->name);
		else if (ft_strcmp(sorted->name, "_") == 0)
			printf("declare -x=\n");
		else
			printf("declare -x %s=%s\n", sorted->name, sorted->value);
		sorted = sorted->next;
	}
	free_env(sorted);
}

/*
 * Validate the syntax of the given command.
 */
static int	validate_syntax(char *arg)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while ((ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (!arg[i])
		return (0);
	if (arg[i] != '=' || arg[0] == '=')
		return (print_stderror(arg), 0);
	if (ft_strchr(arg, '='))
	{
		i = 0;
		while (arg[i])
			if (arg[i++] == '=')
				break ;
		name = ft_substr(arg, 0, i - 2);
		if (ft_isdigit(name[0]))
			return (print_stderror(arg), free(name), 0);
		return (free(name), 1);
	}
	return (0);
}

/*
 * Print messages in stderror
*/
static void	print_stderror(char *str)
{
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" invalid identifier", 2);
}
