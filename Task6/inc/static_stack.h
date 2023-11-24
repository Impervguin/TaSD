#ifndef STATIC_STACK_H__
#define STATIC_STACK_H__

#include <stdio.h>

typedef struct static_stack_t static_stack_t;

#define STATIC_STACK_SIZE 10

/// @brief Реализация стека с помощью статического массива
struct static_stack_t
{
    int *head_ptr; /// Указатель на голову стека
    int *end_ptr; /// Указатель на конец статического массива
    int arr[STATIC_STACK_SIZE]; /// Статический массив
};

void init_static_stack(static_stack_t *stack);
int add_static_stack(static_stack_t *stack, int elem);
int pop_static_stack(static_stack_t *stack, int *elem);
int print_static_stack(FILE *f, const static_stack_t *stack);
int get_static_stack_memory(const static_stack_t *stack);
int static_calculate_expression(int A, int B, int C, int D, int E, int F, int G, int H, int I, int *res);

#endif // STATIC_STACK_H__
