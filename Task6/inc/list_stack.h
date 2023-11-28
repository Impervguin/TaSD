#ifndef LIST_STACK_H__
#define LIST_STACK_H__

#include "static_stack.h"
#include <stdio.h>

typedef struct stack_node_t stack_node_t;

/// @brief Узел стека ввиде односвязного списка
struct stack_node_t
{
    int data; /// Значение узла
    stack_node_t *next; /// Указатель на следующий(более близкий к начальному) элемент стека.
};

void free_stack(stack_node_t **stack);
stack_node_t *create_stack_node(void);
int add_list_stack(stack_node_t **stack, int data);
int pop_list_stack(stack_node_t **stack, int *data);
int list_calculate_expression(int A, int B, int C, int D, int E, int F, int G, int H, int I, int *res);
int get_list_stack_memory(const stack_node_t *stack);

#endif // LIST_STACK_H__

