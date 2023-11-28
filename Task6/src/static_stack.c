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
    if (stack->head_ptr < stack->arr)
        return ERR_EMPTY_STACK;
    
    *elem = *stack->head_ptr;
    stack->head_ptr--;
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

int get_static_stack_memory(const static_stack_t *stack)
{
    return sizeof(stack->end_ptr) + sizeof(stack->head_ptr) + sizeof(int) * (stack->head_ptr - stack->arr + 1);
}

int static_calc(static_stack_t *nums, static_stack_t *ops)
{
    int rc = OK;
    while (ops->head_ptr >= ops->arr && !rc)
    {
        int num1, num2, op;
        rc = pop_static_stack(nums, &num2);
        if (!rc)
            rc = pop_static_stack(nums, &num1);
        
        if (!rc)
            rc = pop_static_stack(ops, &op);
        int res;
        if (!rc)
        {
            switch (op)
            {
                case '+':
                    res = num1 + num2;
                    break;
                case '-':
                    res = num1 - num2;
                    break;
                case '*':
                    res = num1 * num2;
                    break;
                case '/':
                    if (num2 == 0)
                        return ERR_ZERO_DIVISION;
                    res = num1 / num2;
                    break;
            }
            rc = add_static_stack(nums, res);
        }
    }
    return rc;
}

int static_calculate_expression(int A, int B, int C, int D, int E, int F, int G, int H, int I, int *res)
{
    static_stack_t nums, ops;
    init_static_stack(&nums);
    init_static_stack(&ops);
    int rc = OK;
    if (!rc)
        rc = add_static_stack(&nums, A);
    if (!rc)
        rc = add_static_stack(&nums, B);
    if (!rc)
        rc = add_static_stack(&nums, C);
    if (!rc)
        rc = add_static_stack(&nums, D);
    if (!rc)
        rc = add_static_stack(&nums, E);
    if (!rc)
        rc = add_static_stack(&nums, F);
    if (!rc)
        rc = add_static_stack(&ops, '*');
    if (!rc)
        rc = add_static_stack(&ops, '+');
    if (!rc)
        rc = static_calc(&nums, &ops);

    if (!rc)
        rc = add_static_stack(&nums, G);
    if (!rc)
        rc = add_static_stack(&nums, H);
    if (!rc)
        rc = add_static_stack(&ops, '-');
    if (!rc)
        rc = add_static_stack(&ops, '-');   
    if (!rc)
        rc = static_calc(&nums, &ops);
    
    if (!rc)
        rc = add_static_stack(&nums, I);
    if (!rc)
        rc = add_static_stack(&ops, '+');
    if (!rc)
        rc = add_static_stack(&ops, '+');   
    if (!rc)
        rc = static_calc(&nums, &ops);
    
    if (!rc)
        rc = add_static_stack(&ops, '+');
    if (!rc)
        rc = add_static_stack(&ops, '*');   
    if (!rc)
        rc = static_calc(&nums, &ops);
    
    if (!rc)
        rc = pop_static_stack(&nums, res);
    return rc;
}