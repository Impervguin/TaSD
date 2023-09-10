#ifndef LONG_FLOAT_H__
#define LONG_FLOAT_H__

#include <stddef.h>

#define CELL_BASE 4
#define CELL_DEC 10000

#define MAX_MANTISS_SIZE 40

#define ARR_MANTISS_SIZE (MAX_MANTISS_SIZE / CELL_BASE + ((MAX_MANTISS_SIZE % CELL_BASE) != 0))

struct long_float
{
    char mant_sign;
    int mantiss[ARR_MANTISS_SIZE];
    int order;
};

int strtolf(const char *str, struct long_float *lf, size_t max_mant_size, size_t max_order_size);
int check_lf_order(const struct long_float *lf, size_t order_size);
void print_lf(const struct long_float *lf);

#endif
