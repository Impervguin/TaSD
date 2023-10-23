#ifndef OPERATION_H__
#define OPERATION_H__

#include <stdio.h>
#include "list_stack.h"
#include "static_stack.h"

int list_read_operation(FILE *f, stack_node_t **nums, stack_node_t **ops);
int list_calc(stack_node_t **nums, stack_node_t **ops, int *res);
int static_read_operation(FILE *f, static_stack_t *nums, static_stack_t *ops);
int static_calc(static_stack_t *nums, static_stack_t *ops, int *res);

#endif