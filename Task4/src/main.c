#include "static_stack.h"
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
    static_stack_t stack;
    init_static_stack(&stack);
    rc = read_static_stack(f, &stack);
    printf("%d\n", rc);
    if (!rc)
    {
        int tmp;
        pop_static_stack(&stack, &tmp);
        print_static_stack(stdout, &stack);
    }
    fclose(f);
    return OK;
}