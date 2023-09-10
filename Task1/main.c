#include <stdio.h>
#include "long_float.h"
#include "calculus.h"
#include "errs.h"


#define MAX_FIRST_MANTISS_SIZE 35
#define MAX_SECOND_MANTISS_SIZE 40
#define MAX_RESULT_MANTISS_SIZE 40

#define MAX_FIRST_ORDER_SIZE 5
#define MAX_SECOND_ORDER_SIZE 5
#define MAX_RESULT_ORDER_SIZE 5


int main (int argc, char **argv)
{
    struct long_float flf, slf, rlf;
    int rc = ERR_OK;
    // if (argc != 3)
    //     rc = ERR_NO_ARGS;
    // if (!rc)
        rc = strtolf(argv[1], &flf, MAX_FIRST_MANTISS_SIZE, MAX_FIRST_ORDER_SIZE);
    // if (!rc)
        // rc = strtolf(argv[2], &slf, MAX_SECOND_MANTISS_SIZE, MAX_SECOND_ORDER_SIZE);
    // if (!rc)
    // {
    //     multiplication(&flf, &slf, &rlf, ARR_MANTISS_SIZE);
    //     rc = check_lf_order(&rlf, MAX_RESULT_ORDER_SIZE);
    // }
    // if (!rc)
        print_lf(&flf);
    
    return rc;
}
