#include "../../../include/minishell.h"

/*
 * Creates a new redir node
 */
t_redir *create_redir(int type, char *file)
{
        t_redir *redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
        redir->file = file;
        redir->next = NULL;
        return (redir);
}

/*
 * Returns the length of a given redir list.
 */
int     redirs_size(t_redir *list)
{
        int     len;

        len = 0;
        while (list)
        {
                list = list->next;
                len++;
        }
        return (len);
}

/*
 * Returns the last element of a redir list
 */
t_redir *lst_last(t_redir *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*
 * Adds an element to a given redir list.
 */
void    add_redir(t_redir **list, t_redir *redir)
{
	if (*list == NULL)
		*list = redir;
	else
		(lst_last(*list))->next = redir;
}

/*
 * Prints a given cmd list.
 */
void	print_redirs(t_redir *list)
{
	t_redir	*aux;

	aux = list;
	while (aux != NULL)
	{
		printf("Redirection ");
		printf("type: \033[0;31m%s \033[0m", get_str_types(aux->type));
		printf("file: \033[0;35m%s \033[0m\n", aux->file);
		aux = aux->next;
	}
}

/*
 * Frees all the elements of a given cmd list.
 */
void	free_redirs(t_redir *list)
{
	t_redir	*aux;

	while (list != NULL)
	{
		aux = list;
		list = list->next;
		free(aux);
	}
}

/*
 * Gets an element of a redir list by his index.
 */
t_redir	*get_redir_by_index(t_redir *list, int index)
{
	int	i;
	t_redir	*current;

	i = 0;
	current = list;
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
    // Crear una lista de redirecciones
    t_redir *redir_list = NULL;

    // Añadir algunas redirecciones a la lista
    add_redir(&redir_list, create_redir(1, "file1.txt"));
    add_redir(&redir_list, create_redir(2, "file2.txt"));
    add_redir(&redir_list, create_redir(3, "file3.txt"));

    // Imprimir la lista de redirecciones
    printf("Lista de redirecciones:\n");
    print_redirs(redir_list);
    printf("\n");

    // Obtener y imprimir el tamaño de la lista
    int size = redirs_size(redir_list);
    printf("Tamaño de la lista: %d\n", size);

    // Obtener una redirección por índice y imprimirla
    int index = 1;
    t_redir *redir_at_index = get_redir_by_index(redir_list, index);
    if (redir_at_index) {
        printf("Redirección en el índice %d: tipo=%d, archivo=%s\n", index, redir_at_index->type, redir_at_index->file);
    } else {
        printf("No se encontró una redirección en el índice %d\n", index);
    }

    // Liberar la memoria de la lista de redirecciones
    free_redirs(redir_list);

    return 0;
}*/
