#include <stdio.h>
#include <string.h>
#include "io.h"
#include "errs.h"
#include "operation.h"
#include "list_stack.h"
#include "static_stack.h"
#include <time.h>
#include <sys/time.h>

long int get_time(struct timeval *time_s, struct timeval *time_e)
{
    return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
}

#define FILE_INPUT 1
#define USER_INPUT 0

#define LIST_STACK 1
#define STATIC_STACK 0


int main(void)
{
    stack_node_t *list_op = NULL;
    stack_node_t *list_nums = NULL;
    stack_node_t *list_stack = NULL;
    struct timeval start, end;
    long static_time, list_time;
    static_stack_t static_op;
    init_static_stack(&static_op);
    static_stack_t static_nums;
    init_static_stack(&static_nums);
    static_stack_t static_stack;
    init_static_stack(&static_stack);
    FILE *f = NULL;
    int stack_type = 2;
    int command;
    int rc = OK;
    int running = 1;
    int tmp, res, in_t;

    print_intro();

    while ((stack_type != LIST_STACK && stack_type != STATIC_STACK) || rc)
    {
        rc = int_input(&stack_type, "Введите используемый вид стека(0 - статический, 1 - списком): ");
        if (!rc && stack_type != LIST_STACK && stack_type != STATIC_STACK)
            rc = ERR_FORMAT;
        if (rc)
            print_error(rc);     
    }
    
    while (running)
    {
        if (f)
        {
            fclose(f);
            f = NULL;
        }

        rc = OK;
        print_menu();
        
        rc = int_input(&command, "Введите номер: ");
        if (!rc)
            if (command > MAX_COMMAND_NUM || command < 0)
                rc = ERR_COMMAND;
        if (!rc && command == EXIT)
        {
            running = 0;
            continue;
        }
        
        if (!rc)
        {
            switch (command)
            {
            case READ_STACK:
                rc = read_file(&f);
                if (!rc)
                {
                    if (stack_type == STATIC_STACK)
                        rc = read_static_stack(f, &static_stack);
                    else
                        rc = read_list_stack(f, &list_stack);
                }
                break;
            case ADD:
                rc = int_input(&tmp, "Введите целое число: ");
                if (!rc)
                {
                    if (stack_type == STATIC_STACK)
                        rc = add_static_stack(&static_stack, tmp);
                    else
                        rc = add_list_stack(&list_stack, tmp);
                }
                break;
            case POP:
                if (stack_type == STATIC_STACK)
                {
                    rc = pop_static_stack(&static_stack, &tmp);
                }
                else
                    rc = pop_list_stack(&list_stack, &tmp);
                if (!rc)
                    printf("Удаленный элемент: %d\n", tmp);
                break;
            
            case OPERATION:
                rc = int_input(&in_t, "Введите вид ввода(0 - Консольный, 1 - Файловый):");
                if (!rc)
                {
                    if (in_t == USER_INPUT)
                    {
                        printf("Введите выражение: ");
                        if (stack_type == STATIC_STACK)
                        {
                            rc = static_read_operation(stdin, &static_nums, &static_op);
                        }
                        else
                            rc = list_read_operation(stdin, &list_nums, &list_op);
                    }
                    else if (in_t == FILE_INPUT)
                    {
                        rc = read_file(&f);
                        if (!rc)
                        {
                            if (stack_type == STATIC_STACK)
                            {
                                rc = static_read_operation(f, &static_nums, &static_op);
                            }
                            else
                                rc = list_read_operation(f, &list_nums, &list_op);
                        }
                    }
                    else
                        rc = ERR_FORMAT;
                }
                if (!rc)
                {
                    if (stack_type == STATIC_STACK)
                    {
                        rc = static_calc(&static_nums, &static_op, &res);
                    }
                    else
                        rc = list_calc(&list_nums, &list_op, &res);
                }
                if (!rc)
                    printf("Результат выражения:%d\n", res);
                break;

            case COMPARE:
                rc = read_file(&f);
                if (!rc)
                    rc = static_read_operation(f, &static_nums, &static_op);
                
                if (!rc)
                {
                    rc = static2list(&static_nums, &list_nums);
                    if (!rc)
                        rc = static2list(&static_op, &list_op);
                }

                if (!rc)
                {
                    gettimeofday(&start, NULL);
                    rc = list_calc(&list_nums, &list_op, &res);
                    gettimeofday(&end, NULL);
                    list_time = get_time(&start, &end);

                    if (!rc)
                    {
                        gettimeofday(&start, NULL);
                        rc = static_calc(&static_nums, &static_op, &res);
                        gettimeofday(&end, NULL);
                        static_time = get_time(&start, &end);
                    }
                }

                if (!rc)
                {
                    printf("Время вычисления статического стека: %ld мкс.\n", static_time);
                    printf("Время вычисления списка-стека: %ld мкс.\n", list_time);
                }
                break;
            case PRINT:
                if (stack_type == STATIC_STACK)
                {
                    rc = print_static_stack(stdout, &static_stack);
                    if (static_stack.head_ptr < static_stack.arr)
                        printf("Пустой стек.\n");
                }
                else
                {
                    rc = print_list_stack(stdout, list_stack);
                    if (list_stack == NULL)
                        printf("Пустой стек.\n");
                }
    
                break;
            default:
                break;
            }

        }
        print_error(rc);   
    }

    if (f != NULL)
        fclose(f);
    
    free_stack(&list_stack);
    free_stack(&list_nums);
    free_stack(&list_op);
    
    return OK;
}