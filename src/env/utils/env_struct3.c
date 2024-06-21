#include "../../../include/minishell.h"

static void    swap_nodes(t_env *a, t_env *b);

t_env *sort_list(t_env *env)
{
    t_env   *ptr;
    t_env   *l_ptr;
    int     swapped;


    if (!env)
        return NULL;

    l_ptr = NULL;
    while (swapped)
    {
        swapped = 0;
        ptr = env;
        while (ptr->next != l_ptr)
        {
            if (ft_strcmp(ptr->name, ptr->next->name) > 0)
            {
                swap_nodes(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        l_ptr = ptr;
    }
    return (l_ptr);
}


t_env *copy_list(t_env *head) {
    if (!head) return NULL;

    t_env *new_head = create_env(head->name, head->value);
    if (!new_head) return NULL;

    t_env *current = head->next;
    t_env *new_current = new_head;

    while (current) {
        new_current->next = create_env(current->name, current->value);
        if (!new_current->next) {
            return NULL;
        }
        new_current = new_current->next;
        current = current->next;
    }

    return new_head;
}


static void swap_nodes(t_env *a, t_env *b) {
    char *temp_name = a->name;
    char *temp_value = a->value;
    
    a->name = b->name;
    a->value = b->value;
    b->name = temp_name;
    b->value = temp_value;
}

