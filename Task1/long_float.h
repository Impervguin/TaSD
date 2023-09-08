#ifndef LONG_FLOAT_H__
#define LONG_FLOAT_H__

#define CELL_BASE 4
#define MAX_FIRST_MANTISS_SIZE 35
#define MAX_SECOND_MANTISS_SIZE 40
#define MAX_RESULT_MANTISS_SIZE 40

#define FIRST_ARR_MANTISS_SIZE (MAX_FIRST_MANTISS_SIZE/ CELL_BASE + ((MAX_FIRST_MANTISS_SIZE % CELL_BASE) != 0))
#define SECOND_ARR_MANTISS_SIZE (MAX_SECOND_MANTISS_SIZE/ CELL_BASE + ((MAX_SECOND_MANTISS_SIZE % CELL_BASE) != 0))
#define RESULT_ARR_MANTISS_SIZE (MAX_RESULT_MANTISS_SIZE/ CELL_BASE + ((MAX_RESULT_MANTISS_SIZE % CELL_BASE) != 0))

#define MAX_FIRST_ORDER_SIZE 5
#define MAX_SECOND_ORDER_SIZE 5
#define MAX_RESULT_ORDER_SIZE 5

struct first_long_float
{
    char mant_sign;
    int mantiss[FIRST_ARR_MANTISS_SIZE];
    char order_sign;
    int order;
};

struct second_long_float
{
    char mant_sign;
    int mantiss[SECOND_ARR_MANTISS_SIZE];
    char order_sign;
    unsigned order;
};

struct result_long_float
{
    char mant_sign;
    int mantiss[RESULT_ARR_MANTISS_SIZE];
    char order_sign;
    unsigned order;
};

int strtoflf(const char *str, struct first_long_float *flf);
int strtoslf(const char *str, struct second_long_float *slf);
int check_rlf(const struct result_long_float *rlf);
void print_rlf(const struct result_long_float *rlf);

#endif