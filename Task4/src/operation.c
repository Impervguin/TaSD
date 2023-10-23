#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, f) == -1)
        rc =  ERR_IO;

    for (char *ptr = line; !rc;)
    {
        int num, bytes_read;
        if (sscanf(ptr, "%d%n", &num, &bytes_read) != 1)
            rc = ERR_FORMAT;
        
        if (!rc)
        {
            rc = add_list_stack(nums, num);
            ptr += bytes_read;
        }
            
        
        if (!rc)
        {
            while (*ptr == ' ' || *ptr == '\n')
                ptr++;
        
            if (*ptr == '\0')
                break;
            
            if (strchr("+-/*", *ptr) == NULL)
                rc = ERR_FORMAT;
            else
            {
                rc = add_list_stack(ops, (int) *ptr);
                ptr++;
            }
        }
    }
    
    if (rc)
    {
        free_stack(nums);
        free_stack(ops);
    }
    free(line);
    return rc;
}

int static_read_operation(FILE *f, static_stack_t *nums, static_stack_t *ops)
{
    if (f == NULL)
        return ERR_FILE;
    int rc = OK;
    init_static_stack(nums);
    init_static_stack(ops);

    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, f) == -1)
        rc =  ERR_IO;

    for (char *ptr = line; !rc;)
    {
        int num, bytes_read;
        if (sscanf(ptr, "%d%n", &num, &bytes_read) != 1)
            rc = ERR_FORMAT;
        
        if (!rc)
        {
            rc = add_static_stack(nums, num);
            ptr += bytes_read;
        }
            
        
        if (!rc)
        {
            while (*ptr == ' ' || *ptr == '\n')
                ptr++;
        
            if (*ptr == '\0')
                break;
            
            if (strchr("+-/*", *ptr) == NULL)
                rc = ERR_FORMAT;
            else
            {
                rc = add_static_stack(ops, (int) *ptr);
                ptr++;
            }
        }
    }
    
    free(line);
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
    if (nums->head_ptr < nums->arr || ops->head_ptr < ops->arr)
        return ERR_EMPTY_STACK;
    int rc;
    int tmp;
    int op;
    pop_static_stack(nums, &tmp);
    *res = tmp;
    while (nums->head_ptr >= nums->arr && ops->head_ptr >= ops->arr)
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

    if (nums->head_ptr >= nums->arr || ops->head_ptr >= ops->arr)
        return ERR_OP_PARAMS;
    return OK;
}