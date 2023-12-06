#include <stdio.h>
#include "errs.h"
#include "btree.h"
#include "int_btree.h"
#include "open_hash_table.h"
#include "io.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

long int get_time(struct timespec *time_s, struct timespec *time_e)
{
    return (time_e -> tv_sec * 1000000000 + time_e -> tv_nsec) - (time_s -> tv_sec * 1000000000 + time_s -> tv_nsec);
}

int main(void)
{
    btree_node *calc_root = NULL;
    int_node_t *broot = NULL;
    int_node_t *avlroot = NULL;
    ohash_table_t table;
    int *arr = NULL;
    size_t arr_size = 0;
    init_open_hash(&table);
    struct timespec st, ed;
    long tree_time, avl_time, hash_time;
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
        print_menu();
        int tA, tB, tC, tD, tE, tF, tG, tH, tI;
        int itmp;
        size_t cmp_cnt = 0;
        rc = int_input(&command, "");
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
            case BADD:
                rc = int_input(&itmp, "Введите число для добавления в дерево: ");
                if (!rc)
                {
                    if (inttree_find(broot, itmp, &cmp_cnt))
                        rc = ERR_ALREADY_IN;
                    if (!rc)
                    {
                        broot = inttree_add(broot, itmp);
                        if (inttree_find(broot, itmp, &cmp_cnt))
                            printf("Символ успешно добавлен в дерево.\n");
                        else
                            rc = ERR_MEMORY;
                    } 
                }
                break;
            case BFIND:
                rc = int_input(&itmp, "Введите число для поиска в дереве: ");
                if (!rc)
                {
                    if (inttree_find(broot, itmp, &cmp_cnt))
                        printf("Число есть в дереве, число сравнений - %zu.\n", cmp_cnt);
                    else
                        rc = ERR_NOT_FOUND;
                }
                break;
            case BDELETE:
                rc = int_input(&itmp, "Введите число для удаления из дерева: ");
                if (!rc)
                {
                    if (!inttree_find(broot, itmp, &cmp_cnt))
                        rc = ERR_NOT_FOUND;
                    if (!rc)
                    {
                        broot = inttree_delete(broot, itmp);
                        if (!inttree_find(broot, itmp, &cmp_cnt))
                            printf("Символ успешно удален из дерева.\n");
                        else
                            rc = ERR_MEMORY;
                    } 
                }
                break;
            case BPRINT:
                dot = fopen(dotfname, "w");
                if (!dot)
                    rc = ERR_FILE;
                if (!rc)
                    rc = intree_dot_print(dot, broot);
                if (dot)
                    fclose(dot);
                if (!rc)
                {
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                }
                break;
                case AVLADD:
                rc = int_input(&itmp, "Введите число для добавления в АВЛ-дерево: ");
                if (!rc)
                {
                    if (inttree_find(avlroot, itmp, &cmp_cnt))
                        rc = ERR_ALREADY_IN;
                    if (!rc)
                    {
                        avlroot = intavl_add(avlroot, itmp);
                        if (inttree_find(avlroot, itmp, &cmp_cnt))
                            printf("Символ успешно добавлен в АВЛ-дерево.\n");
                        else
                            rc = ERR_MEMORY;
                    } 
                }
                break;
            case AVLFIND:
                rc = int_input(&itmp, "Введите число для поиска в АВЛ-дереве: ");
                if (!rc)
                {
                    if (inttree_find(avlroot, itmp, &cmp_cnt))
                        printf("Число есть в АВл-дереве, число сравнений - %zu\n", cmp_cnt);
                    else
                        rc = ERR_NOT_FOUND;
                }
                break;
            case AVLDELETE:
                rc = int_input(&itmp, "Введите число для удаления из АВЛ-дерева: ");
                if (!rc)
                {
                    if (!inttree_find(avlroot, itmp, &cmp_cnt))
                        rc = ERR_NOT_FOUND;
                    if (!rc)
                    {
                        avlroot = intavl_delete(avlroot, itmp);
                        if (!inttree_find(avlroot, itmp, &cmp_cnt))
                            printf("Символ успешно удален из АВЛ-дерева.\n");
                        else
                            rc = ERR_MEMORY;
                    } 
                }
                break;
            case AVLPRINT:
                dot = fopen(dotfname, "w");
                if (!dot)
                    rc = ERR_FILE;
                if (!rc)
                    rc = intree_dot_print(dot, avlroot);
                if (dot)
                    fclose(dot);
                if (!rc)
                {
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                }
                break;
            case HASHADD:
                rc = int_input(&itmp, "Введите число для добавления в хэш-таблицу: ");
                if (!rc)
                {
                    rc = add_open_hash(&table, itmp);
                    if (!rc)
                        printf("Число добавлено в хэш-таблицу.\n");
                }
                break;
            case HASHFIND:
                rc = int_input(&itmp, "Введите число для поиска в хэш-таблице: ");
                if (!rc)
                {
                    rc = find_open_hash(&table, itmp, &cmp_cnt);
                    if (!rc)
                        printf("Число найдено в хэш-таблице, число сравнений - %zu\n", cmp_cnt);
                }
                break;
            case HASHDELETE:
                rc = int_input(&itmp, "Введите число для удаления из хэш-таблицы: ");
                if (!rc)
                {
                    rc = delete_open_hash(&table, itmp);
                    if (!rc)
                        printf("Число удалено из хэш-таблицы.\n");
                }
                break;
            case HASHRESTRUCT:
                rc = int_input(&itmp, "Введите новый размер хэш-таблицы: ");
                if (!rc && itmp <= 0)
                    rc = ERR_FORMAT;
                if (!rc)
                {
                    rc = restruct_open_hash(&table, (size_t) itmp);
                }
                break;
            case HASHPRINT:
                print_ohash_table(&table);
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
                    btree_postfix_calculate(&calc_root);
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
                    if (arr != NULL)
                        free(arr);
                    arr_size = 0;
                    arr = btree_infix_arr(calc_root, &arr_size);
                    printf("Полученный массив:");
                    for (size_t i = 0; i < arr_size; i++)
                        printf("%d ", arr[i]);
                    printf("\n");
                }
                break;
            case ARRBTREE:
                if (arr == NULL)
                    printf("Массив пустой.\n");
                else
                    broot = arr_in_inttree(arr, arr_size);
                break;
            case ARRAVLTREE:
                if (arr == NULL)
                    printf("Массив пустой.\n");
                else
                    avlroot = arr_in_intavl(arr, arr_size);
                break;
            case ARRHASH:
                if (arr == NULL)
                    printf("Массив пустой.\n");
                else
                    rc = arr_in_open_hash(&table, arr, arr_size);
                break;
            case COMPARE:
                rc = int_input(&itmp, "Введите число для поиска: ");
                if (rc)
                    break;
                clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                int_node_t *tmp = inttree_find(broot, itmp, &cmp_cnt);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                if (tmp)
                    printf("Элемент найден в дереве за %zu сравнений.\n", cmp_cnt);
                else
                    printf("Элемент не найден в дереве за %zu сравнений.\n", cmp_cnt);

                tree_time = get_time(&st, &ed);
                cmp_cnt = 0;
                clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                tmp = inttree_find(avlroot, itmp, &cmp_cnt);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                if (tmp)
                    printf("Элемент найден в сбалансированном дереве за %zu сравнений.\n", cmp_cnt);
                else
                    printf("Элемент не найден в сбалансированном дереве за %zu сравнений.\n", cmp_cnt);
                avl_time = get_time(&st, &ed);

                cmp_cnt = 0;
                clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                rc = find_open_hash(&table, itmp, &cmp_cnt);
                clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                if (!rc)
                    printf("Элемент найден в таблице за %zu сравнений.\n", cmp_cnt);
                else
                    printf("Элемент не найден в таблице за %zu сравнений.\n", cmp_cnt);

                hash_time = get_time(&st, &ed);
                printf("\n");
                printf("Время поиска деревом - %ld нс.\n", tree_time);
                printf("Время поиска АВЛ-деревом - %ld нс.\n", avl_time);
                printf("Время поиска Хэш-таблицей - %ld нс.\n", hash_time);
                printf("\n");
                printf("Объем памяти дерева - %zu  байт.\n", inttree_memory(broot));
                printf("Объем памяти АВЛ-деревом - %zu  байт.\n", inttree_memory(avlroot));
                printf("Объем памяти хэш-таблицы - %zu  байт.\n", open_hash_memory(&table));
                rc = OK;
                break;
            default:
                rc = ERR_COMMAND;
            }
        }
        print_error(rc); 
        printf("\n");  
    }
    btree_free(&calc_root);
    free_inttree(&broot);
    free_inttree(&avlroot);
    free_open_hash(&table);
    return OK;
}


