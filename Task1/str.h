#ifndef STR_H__
#define STR_H__

#include <stddef.h>

int str_input(char *str, size_t max_size);
void print_float_ruler(size_t max_mantiss_size, size_t max_order_size);
void print_intro(size_t first_mant, size_t first_order, size_t sec_mant, size_t sec_order, size_t str_size);

#endif
