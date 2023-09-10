#ifndef LONG_FLOAT_H__
#define LONG_FLOAT_H__

#include <stddef.h>

#define MAX_MANTISS_SIZE 40
#define CELL_BASE 10


struct long_float
{
    char mant_sign;
    int mantiss[MAX_MANTISS_SIZE];
    int order;
    size_t size;
};
void make_lf_null(struct long_float *lf);
int strtolf(const char *str, struct long_float *lf, size_t max_mant_size, size_t max_order_size);
int check_lf_order(const struct long_float *lf, size_t order_size);
void print_lf(const struct long_float *lf);

#endif
