#include <stdio.h>
#include "static_stack.h"
#include "errs.h"

void init_static_stack(static_stack_t *stack)
{
    stack->head_ptr = stack->arr - 1;
    stack->end_ptr = stack->arr + STATIC_STACK_SIZE;
}

int add_static_stack(static_stack_t *stack, int elem)
{
    if (stack->head_ptr + 1 == stack->end_ptr)
        return ERR_STACK_OVERFLOW;
    
    stack->head_ptr++;
    *(stack->head_ptr) = elem;
    return OK;
}

int pop_static_stack(static_stack_t *stack, int *elem)
{
    if (stack->end_ptr < stack->arr)
        return ERR_EMPTY_STACK;
    
    *elem = *stack->head_ptr;
    stack->head_ptr--;
    return OK;
}

int read_static_stack(FILE *f, static_stack_t *stack)
{
    int elem;
    if (f == NULL)
        return ERR_FILE;
    
    stack->head_ptr = stack->arr - 1;
    while (fscanf(f, "%d", &elem) == 1)
        if (add_static_stack(stack, elem))
            return ERR_STACK_OVERFLOW;

    if (!feof(f))
        return ERR_FILE_IO;
    
    return OK;
    
}

int print_static_stack(FILE *f, const static_stack_t *stack)
{
    if (f == NULL)
        return ERR_FILE;
    
    for (int *p = stack->head_ptr; p >= stack->arr; p--)
        if (fprintf(f, "%d\n", *p) < 0)
            return ERR_FILE_IO;
    
    return OK;
}