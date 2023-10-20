#include "static_stack.h"
#include "list_stack.h"
#include "errs.h"
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
    rc = read_list_stack(f, &stack);
    printf("%d\n", rc);
    if (!rc)
    {
        int tmp;
        pop_list_stack(&stack, &tmp);
        print_list_stack(stdout, stack);
    }
    free_stack(stack);
    fclose(f);
    return OK;
}