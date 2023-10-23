#ifndef LIST_STACK_H__
#define LIST_STACK_H__

#include <stdio.h>

typedef struct stack_node_t stack_node_t;

struct stack_node_t
{
    int data;
    stack_node_t *next;
};

void free_stack(stack_node_t **stack);
stack_node_t *create_stack_node(void);
int add_list_stack(stack_node_t **stack, int data);
int pop_list_stack(stack_node_t **stack, int *data);
int read_list_stack(FILE *f, stack_node_t **stack);
int print_list_stack(FILE *f, const stack_node_t *stack);

#endif