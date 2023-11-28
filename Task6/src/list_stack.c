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

int get_list_stack_memory(const stack_node_t *stack)
{
    int mem = sizeof(stack);
    for (; stack != NULL; stack = stack->next)
        mem += sizeof(*stack);
    return mem;
}

int list_calc(stack_node_t **nums, stack_node_t **ops)
{
    int rc = OK;
    while (*ops != NULL && !rc)
    {
        int num1, num2, op;
        rc = pop_list_stack(nums, &num2);
        if (!rc)
            rc = pop_list_stack(nums, &num1);
        
        if (!rc)
            rc = pop_list_stack(ops, &op);
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
            rc = add_list_stack(nums, res);
        }
    }
    return rc;
}

int list_calculate_expression(int A, int B, int C, int D, int E, int F, int G, int H, int I, int *res)
{
    stack_node_t *nums = NULL, *ops = NULL;
    int rc = OK;
    if (!rc)
        rc = add_list_stack(&nums, A);
    if (!rc)
        rc = add_list_stack(&nums, B);
    if (!rc)
        rc = add_list_stack(&nums, C);
    if (!rc)
        rc = add_list_stack(&nums, D);
    if (!rc)
        rc = add_list_stack(&nums, E);
    if (!rc)
        rc = add_list_stack(&nums, F);
    if (!rc)
        rc = add_list_stack(&ops, '*');
    if (!rc)
        rc = add_list_stack(&ops, '+');
    if (!rc)
        rc = list_calc(&nums, &ops);

    if (!rc)
        rc = add_list_stack(&nums, G);
    if (!rc)
        rc = add_list_stack(&nums, H);
    if (!rc)
        rc = add_list_stack(&ops, '-');
    if (!rc)
        rc = add_list_stack(&ops, '-');   
    if (!rc)
        rc = list_calc(&nums, &ops);
    
    if (!rc)
        rc = add_list_stack(&nums, I);
    if (!rc)
        rc = add_list_stack(&ops, '+');
    if (!rc)
        rc = add_list_stack(&ops, '+');   
    if (!rc)
        rc = list_calc(&nums, &ops);
    
    if (!rc)
        rc = add_list_stack(&ops, '+');
    if (!rc)
        rc = add_list_stack(&ops, '*');   
    if (!rc)
        rc = list_calc(&nums, &ops);
    
    if (!rc)
        rc = pop_list_stack(&nums, res);
    free_stack(&nums);
    free_stack(&ops);
    return rc;
}