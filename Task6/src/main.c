#include <stdio.h>
#include "errs.h"
#include "io.h"
#include "list_stack.h"
#include "static_stack.h"
#include "btree.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

long int get_time(struct timespec *time_s, struct timespec *time_e)
{
    return (time_e -> tv_sec * 1000000000 + time_e -> tv_nsec) - (time_s -> tv_sec * 1000000000 + time_s -> tv_nsec);
}

int main(void)
{
    btree_node *root = NULL;
    btree_node *calc_root = NULL;
    struct timespec st, ed;
    long tree_time, static_time, list_time;
    int command;
    int rc = OK;
    int running = 1;
    int A = 1, B = 2, C = 3, D = 4, E = 5, F = 6, G = 7, H = 8, I = 9;

    print_intro();

    while (running)
    {
        rc = OK;
        char *dotfname = "tmp.dot";
        FILE *dot;
        char ctmp;
        print_menu();
        int tA, tB, tC, tD, tE, tF, tG, tH, tI;
        int itmp;
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
            case ADD:
                rc = char_input(&ctmp, "Введите символ для добавления в дерево: ");
                if (!rc)
                    rc = btree_addchar(&root, ctmp);
                if (!rc)
                    printf("Символ успешно добавлен в дерево.\n");
                break;
            case FIND:
                rc = char_input(&ctmp, "Введите символ для поиска в дереве: ");
                if (!rc)
                    rc = btree_findchar(root, ctmp);
                if (!rc)
                    printf("Символ найден в дереве.\n");
                break;
            case DELETE:
                rc = char_input(&ctmp, "Введите символ для поиска в дереве: ");
                if (!rc)
                    rc = btree_deletechar(&root, ctmp);
                if (!rc)
                    printf("Символ успешно удален из дерева.\n");
                break;
            case PRINT:
                dot = fopen(dotfname, "w");
                if (!dot)
                    rc = ERR_FILE;
                if (!rc)
                    rc = btree_dot_print(dot, root);
                if (dot)
                    fclose(dot);
                if (!rc)
                {
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                }
                break;
            case PREFIX:
                if (!root)
                    printf("Пустое дерево.\n");
                else
                    btree_prefix_bypass(root);
                break;
            case INFIX:
                if (!root)
                    printf("Пустое дерево.\n");
                else
                    btree_infix_bypass(root);
                break;
            case POSTFIX:
                if (!root)
                    printf("Пустое дерево.\n");
                else
                    btree_postfix_bypass(root);
                break;
            case CHANGE:
                printf("Нынешние значения:\n");
                printf("А = %d\n", A);
                printf("B = %d\n", B);
                printf("C = %d\n", C);
                printf("D = %d\n", D);
                printf("E = %d\n", E);
                printf("F = %d\n", F);
                printf("G = %d\n", G);
                printf("H = %d\n", H);
                printf("I = %d\n", I);
                rc = int_input(&tA, "Введите переменную A: ");
                if (!rc)
                    rc = int_input(&tB, "Введите переменную B: ");
                if (!rc)
                    rc = int_input(&tC, "Введите переменную C: ");
                if (!rc)
                    rc = int_input(&tD, "Введите переменную D: ");
                if (!rc)
                    rc = int_input(&tE, "Введите переменную E: ");
                if (!rc)
                    rc = int_input(&tF, "Введите переменную F: ");
                if (!rc)
                    rc = int_input(&tG, "Введите переменную G: ");
                if (!rc)
                    rc = int_input(&tH, "Введите переменную H: ");
                if (!rc)
                    rc = int_input(&tI, "Введите переменную I: ");
                if (!rc)
                    A = tA, B = tB, C = tC, D = tD, E = tE, F = tF, G = tG, H = tH, I = tI;
                break;
            case CALC:
                rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
                if (!rc)
                {
                    dot = fopen(dotfname, "w");
                    if (!dot)
                        rc = ERR_FILE;
                    if (!rc)
                        rc = btree_dot_print(dot, calc_root);
                    if (dot)
                    fclose(dot);
                }
                if (!rc)
                {
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                    rc = btree_calculate(&calc_root, &itmp);
                    if (!rc)
                        printf("Результат вычисления: %d.\n", itmp);
                    btree_free(&calc_root);
                }
                break;
            case COMPARE:
                rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
                if (rc)
                    break;
                
                
                
                clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                rc = btree_calculate(&calc_root, &itmp);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                if (rc)
                    break;
                tree_time = get_time(&st, &ed);

                clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                rc = static_calculate_expression(A, B, C, D, E, F, G, H, I, &itmp);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                if (rc)
                    break;
                static_time = get_time(&st, &ed);


                clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                rc = list_calculate_expression(A, B, C, D, E, F, G, H, I, &itmp);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                if (rc)
                    break;
                list_time = get_time(&st, &ed);

                printf("Время подсчета деревом - %ld нс.\n", tree_time);
                printf("Время подсчета статическим стеком - %ld нс.\n", static_time);
                printf("Время подсчета стеком-списком - %ld нс.\n", list_time);

                break;
            default:
                rc = ERR_COMMAND;
            }
        }
        print_error(rc);   
    }
    btree_free(&root);
    return OK;
}


