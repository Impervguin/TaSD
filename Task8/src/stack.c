#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
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