#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "open_hash_table.h"
#include "errs.h"


size_t open_hash(int num, size_t size)
{
    return ((size_t) num) * HASH_MULT_CONST % size;
}

int init_open_hash(ohash_table_t *table)
{
    table->arr = calloc(INIT_SIZE, sizeof(int_list));
    if (table->arr)
    {
        table->size = INIT_SIZE;
        return OK;
    }
    return ERR_MEMORY;
}

void clear_open_hash(ohash_table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
        int_list_free(&table->arr[i]);
}

void free_open_hash(ohash_table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
        int_list_free(&table->arr[i]);
    free(table->arr);
    table->arr = NULL;
    table->size = 0;
}

size_t open_hash_count(ohash_table_t *table)
{
    size_t count = 0;
    for (size_t i = 0; i < table->size; i++)
        count += int_list_count(table->arr[i].start);
    return count;
}

int add_open_hash(ohash_table_t *table, int num)
{
    size_t ind = open_hash(num, table->size);
    return int_list_add(&table->arr[ind], num);

}

int delete_open_hash(ohash_table_t *table, int num)
{
    size_t ind = open_hash(num, table->size);
    return int_list_remove(&table->arr[ind], num);
}

int find_open_hash(ohash_table_t *table, int num, size_t *cmp_cnt)
{
    size_t ind = open_hash(num, table->size);
    return int_list_find(table->arr[ind].start, num, cmp_cnt);
}

int resize_open_hash(ohash_table_t *table, size_t size)
{
    size_t prev_size = table->size;
    int_list *tmp = realloc(table->arr, size * sizeof(int_list));
    if (tmp)
    {
        table->arr = tmp;
        table->size = size;
        if (prev_size < size)
            memset(table->arr + prev_size, 0, sizeof(int_list) * (size - prev_size));
        return OK;
    }
    return ERR_MEMORY;
}

void fill_hash_table(ohash_table_t *table, int_list *list)
{
    int_listnode_t *next;
    for (int_listnode_t *now = list->start; now != NULL; now = next)
    {
        next = now->next;
        size_t ind = open_hash(now->data, table->size);
        int_list_add_node(&table->arr[ind], now);
    }
}

int restruct_open_hash(ohash_table_t *table, size_t new_size)
{
    int_list tmp = {NULL, NULL};
    for (size_t i = 0; i < table->size; i++)
    {
        int_listnode_t *next;
        for (int_listnode_t *now = table->arr[i].start; now != NULL; now = next)
        {
            next = now->next;
            int_list_add_node(&tmp, now);
        }
        table->arr[i].start = NULL;
        table->arr[i].end = NULL;
    }
    int rc = resize_open_hash(table, new_size);
    fill_hash_table(table, &tmp);
    return rc;
}

void print_ohash_table(ohash_table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
    {
        if (table->arr[i].start == NULL)
            continue;
        printf("%zu - ", i);
        print_int_list(&table->arr[i]);
    }
}

int arr_in_open_hash(ohash_table_t *table, int *arr, size_t size)
{
    int rc = OK;
    for (size_t i = 0; i < size && (!rc || rc == ERR_ALREADY_IN) ; i++)
        rc = add_open_hash(table, arr[i]);
    if (rc == ERR_ALREADY_IN)
        rc = OK;
    return rc;
}

size_t open_hash_memory(ohash_table_t *table)
{
    size_t mem = 0;
    for (size_t i = 0; i < table->size; i++)
        mem += int_list_memory(&table->arr[i]);
    return mem;
}