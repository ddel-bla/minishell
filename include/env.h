#ifndef ENV_H
# define ENV_H
// .......... STRUCTS ...........
// -------- REDIRECTION ---------
typedef struct s_env
{
	char		*name;
	char		*value;
	struct s_env	*next;
}			t_env;
// .......... FUNCTIONS ...........
void	save_env(t_env **list, char **envp);
t_env	*create_env(char *name, char *value);
int	env_size(t_env *list);
void	add_env(t_env **list, t_env *env);
void	print_env(t_env *list);
void	free_env(t_env *list);
t_env	*get_env_by_index(t_env *list, int index);
t_env	*get_env_by_name(t_env *list, char *name);
void	delete_env_by_name(t_env *list, char *name);
#endif
