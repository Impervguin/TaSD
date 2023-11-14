#include <stdio.h>
#include <stdlib.h>
#include "list_stack.h"
#include "errs.h"

void free_stack(stack_node_t **stack)
{
    if (*stack == NULL)
        return;
    
    stack_node_t *now = *stack;
    while (now != NULL)
    {
        stack_node_t *tmp = now->next;
        free(now);
        now = tmp;
    }
    *stack = NULL;
}

stack_node_t *create_stack_node(void)
{
    return calloc(sizeof(stack_node_t), 1);
}

int add_list_stack(stack_node_t **stack, int data)
{
    stack_node_t *tmp = create_stack_node();
    if (tmp == NULL)
        return ERR_MEMORY;
    
    tmp->data = data;
    tmp->next = *stack;
    *stack = tmp;
    return OK;
}

int pop_list_stack(stack_node_t **stack, int *data)
{
    if (*stack == NULL)
        return ERR_EMPTY_STACK;
    *data = (*stack)->data;
    stack_node_t *tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);
    return OK;
}

int read_list_stack(FILE *f, stack_node_t **stack)
{
    int elem;
    if (f == NULL)
        return ERR_FILE;
    
    stack_node_t *tmp = NULL;

    while (fscanf(f, "%d", &elem) == 1)
    {
        if (add_list_stack(&tmp, elem))
        {
            free_stack(&tmp);
            return ERR_MEMORY;
        }
    }
    

    if (!feof(f))
    {
        free_stack(&tmp);
        return ERR_FILE_IO;
    }

    free_stack(stack);
    *stack = tmp;
    return OK;
}


int print_list_stack(FILE *f, const stack_node_t *stack)
{
    if (f == NULL)
        return ERR_FILE;
    
    for (const stack_node_t *p = stack; p != NULL; p = p->next)
        if (fprintf(f, "%d\n", p->data) < 0)
            return ERR_FILE_IO;
    
    return OK;
}

int static2list(const static_stack_t *static_stack, stack_node_t **list)
{
    stack_node_t *tmp = NULL;
    for (const int *ptr = static_stack->arr; ptr <= static_stack->head_ptr; ptr++)
    {
        if (add_list_stack(&tmp, *ptr))
        {
            free_stack(&tmp);
            return ERR_MEMORY;
        }
    }

    free_stack(list);
    *list = tmp;
    return OK;
}

int get_list_stack_memory(const stack_node_t *stack)
{
    int mem = sizeof(stack);
    for (; stack != NULL; stack = stack->next)
        mem += sizeof(*stack);
    return mem;
}