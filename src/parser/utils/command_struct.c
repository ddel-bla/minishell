#include "../../../include/minishell.h"

/*
 * Creates a new commmand node.
 */
t_cmd *create_cmd(char **arg, int operator_type, t_redir *redir)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = arg;
	cmd->operator_type = operator_type;
	cmd->redirection = redir;
	cmd->next = NULL;
	return (cmd);
}

/*
 * Returns the length of a given cmd list.
 */
int	cmd_size(t_cmd *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

/*
 * Return the last element of a cmd list.
 */
t_cmd	*cmd_last(t_cmd	*list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given cmd list.
 */
void	add_cmd(t_cmd **list, t_cmd *cmd)
{
	if (*list == NULL)
		*list = cmd;
	else
		(cmd_last(*list))->next = cmd;
}

/*
 * Prints a given cmd list.
 */
void	print_cmd(t_cmd *list)
{
	t_cmd	*aux;
	int	i;

	aux = list;
	while (aux != NULL)
	{
		printf("Command\n");
		i = 0;
		while (aux->cmd[i])
		{
			printf("%d argument: \033[0;31m %s \033[0m\n",i, aux->cmd[i]);
			i++;
		}
		printf("Operator type: \033[0;35m%s \033[0m\n", get_str_types(aux->operator_type));
		print_redirs(aux->redirection);
		aux = aux->next;
	}
}

/*
 * Frees all the elements of a given list.
 */
void	free_cmd(t_cmd *list)
{
	t_cmd	*aux;
	t_cmd	*next;
	
	aux = list;
	while (aux != NULL)
	{
		next = aux->next;
		free(aux->cmd);
		free(aux);
		aux = next;
	}
}

/*
 * Gets an element of a cmd list by his index.
 */
t_cmd	*get_cmd_by_index(t_cmd *cmd, int index)
{
	int	i;
	t_cmd	*current;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		if (index == i)
			return current;
		current = current->next;
		i++;
	}
	return (NULL);
}
/*
int main() {
    // Crear algunas redirecciones
    t_redir *redir1 = (t_redir *)malloc(sizeof(t_redir));
    redir1->type = 1;
    redir1->file = strdup("file1.txt");
    redir1->next = NULL;

    t_redir *redir2 = (t_redir *)malloc(sizeof(t_redir));
    redir2->type = 2;
    redir2->file = strdup("file2.txt");
    redir2->next = NULL;

    // Crear una lista de comandos
    t_cmd *cmd_list = NULL;

    // Crear algunos argumentos
    char *args1[] = {"ls", "-l", NULL};
    char *args2[] = {"grep", "main", NULL};

    // Añadir algunos comandos a la lista
    add_cmd(&cmd_list, create_cmd(args1, 0, redir1));
    add_cmd(&cmd_list, create_cmd(args2, 1, redir2));

    // Imprimir la lista de comandos
    printf("Lista de comandos:\n");
    print_cmd(cmd_list);
    printf("\n");

    // Obtener y imprimir el tamaño de la lista
    int size = cmd_size(cmd_list);
    printf("Tamaño de la lista: %d\n", size);

    // Obtener un comando por índice y imprimirlo
    int index = 1;
    t_cmd *cmd_at_index = get_cmd_by_index(cmd_list, index);
    if (cmd_at_index) {
        printf("Comando en el índice %d:\n", index);
        for (int i = 0; cmd_at_index->cmd[i] != NULL; i++) {
            printf("Argumento %d: %s\n", i, cmd_at_index->cmd[i]);
        }
        printf("Tipo de operador: %d\n", cmd_at_index->operator_type);
        printf("Redirección:\n");
        print_redirs(cmd_at_index->redirection);
    } else {
        printf("No se encontró un comando en el índice %d\n", index);
    }

    // Liberar la memoria de la lista de comandos
    free_cmd(cmd_list);

    return 0;
}*/
