#ifndef STACK_H__
#define STACK_H__

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

#endif // STACK_H__
