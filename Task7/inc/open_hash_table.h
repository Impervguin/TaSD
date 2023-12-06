#ifndef OPEN_HASH_TABLE_H__
#define OPEN_HASH_TABLE_H__

#include <stdio.h>
#include "int_list.h"

typedef struct ohash_table_t ohash_table_t;

#define INIT_SIZE 5
#define RESTRUCT_INC 4
#define DEFAULT_RESTRUCT_CMP 3
#define HASH_MULT_CONST 1

struct ohash_table_t
{
    int_list *arr;
    size_t size;
};


size_t open_hash(int num, size_t size);

int init_open_hash(ohash_table_t *table);
size_t open_hash_count(ohash_table_t *table);
int add_open_hash(ohash_table_t *table, int num);
int delete_open_hash(ohash_table_t *table, int num);
int find_open_hash(ohash_table_t *table, int num, size_t *cmp_cnt);
int resize_open_hash(ohash_table_t *table, size_t size);
int restruct_open_hash(ohash_table_t *table, size_t new_size);
void print_ohash_table(ohash_table_t *table);
void free_open_hash(ohash_table_t *table);
void clear_open_hash(ohash_table_t *table);
int arr_in_open_hash(ohash_table_t *table, int *arr, size_t size);

size_t open_hash_memory(ohash_table_t *table);
#endif // OPEN_HASH_TABLE_H__
