#include <stdio.h>
#include <string.h>
#include "operation.h"
#include "static_stack.h"
#include "list_stack.h"
#include "errs.h"

int list_read_operation(FILE *f, stack_node_t **nums, stack_node_t **ops)
{
    if (f == NULL)
        return ERR_FILE;
    int rc = OK;
    free_stack(nums);
    free_stack(ops);

    int num;
    int symb;
    while (!rc)
    {
        if (fscanf(f, "%d", &num) != 1)
        {
            rc = ERR_FILE_IO;
            break;
        }

        while ((symb = getc(f)) == ' ' || (symb == '\n'));
        
        if (strchr("+-*/", symb) == NULL)
        {
            if (feof(f))
            {
                rc = add_list_stack(nums, num);
                break;
            }
            else
            {
                rc = ERR_FILE_IO;
                break;
            }
        }

        if (add_list_stack(ops, symb) || add_list_stack(nums, num))
        {
            rc = ERR_MEMORY;
            break;
        }  
    }
    
    if (rc)
    {
        free_stack(nums);
        free_stack(ops);
    }
    return rc;
}


int static_read_operation(FILE *f, static_stack_t *nums, static_stack_t *ops)
{
    if (f == NULL)
        return ERR_FILE;
    int rc = OK;

    init_static_stack(nums);
    init_static_stack(ops);

    int num;
    int symb;
    while (!rc)
    {
        if (fscanf(f, "%d", &num) != 1)
        {
            rc = ERR_FILE_IO;
            break;
        }

        while ((symb = getc(f)) == ' ' || (symb == '\n'));
        
        if (strchr("+-*/", symb) == NULL)
        {
            if (feof(f))
            {
                rc = add_static_stack(nums, num);
                break;
            }
            else
            {
                rc = ERR_FILE_IO;
                break;
            }
        }

        if (add_static_stack(ops, symb) || add_static_stack(nums, num))
        {
            rc = ERR_STACK_OVERFLOW;
            break;
        }  
    }
    
    return rc;
}

int list_calc(stack_node_t **nums, stack_node_t **ops, int *res)
{
    if (*nums == NULL || *ops == NULL)
        return ERR_EMPTY_STACK;
    int rc;
    int tmp;
    int op;
    pop_list_stack(nums, &tmp);
    *res = tmp;
    while (*nums != NULL && *ops != NULL)
    {
        if ((rc = pop_list_stack(ops, &op)))
            return rc;
        if ((rc = pop_list_stack(nums, &tmp)))
            return rc;
        
        switch (op)
        {
        case '+':
            *res += tmp;
            break;
        case '-':
            *res -= tmp;
            break;
        case '*':
            *res *= tmp;
            break;
        case '/':
            if (tmp == 0)
                return ERR_ZERO_DIVISION;
            *res /= tmp;
            break;
        default:
            return ERR_UNKNOWN_OP;
            break;
        }
    }
    if (*nums != NULL || *ops != NULL)
        return ERR_OP_PARAMS;
    return OK;
}


int static_calc(static_stack_t *nums, static_stack_t *ops, int *res)
{
    if (nums->head_ptr < nums->arr || ops->end_ptr < ops->arr)
        return ERR_EMPTY_STACK;
    int rc;
    int tmp;
    int op;
    pop_static_stack(nums, &tmp);
    *res = tmp;
    while (nums->head_ptr >= nums->arr && ops->end_ptr >= ops->arr)
    {
        if ((rc = pop_static_stack(ops, &op)))
            return rc;
        if ((rc = pop_static_stack(nums, &tmp)))
            return rc;
        
        switch (op)
        {
        case '+':
            *res += tmp;
            break;
        case '-':
            *res -= tmp;
            break;
        case '*':
            *res *= tmp;
            break;
        case '/':
            if (tmp == 0)
                return ERR_ZERO_DIVISION;
            *res /= tmp;
            break;
        default:
            return ERR_UNKNOWN_OP;
            break;
        }
    }

    if (nums->head_ptr >= nums->arr || ops->end_ptr >= ops->arr)
        return ERR_OP_PARAMS;
    return OK;
}