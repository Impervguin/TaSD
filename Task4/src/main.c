#include "static_stack.h"
#include "list_stack.h"
#include "errs.h"
#include "operation.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return 2;
    int rc;
    stack_node_t *stack = NULL;
    stack_node_t *ops = NULL;
    rc = list_read_operation(f, &stack, &ops);
    printf("%d\n", rc);
    if (!rc)
    {
        int tmp;
        rc = list_calc(&stack, &ops, &tmp);
        printf("%d\n", rc);
        printf("%d\n", tmp);
    }
    free_stack(&stack);
    free_stack(&ops);
    fclose(f);
    return OK;
}