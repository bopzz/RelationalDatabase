#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define FAILED NULL
#define TABLE_SIZE 197

typedef struct TUPLE *TUPLELIST;
struct TUPLE {
    int key;
    int size;
    int tableSize;
    char **data;
    TUPLELIST next;
};
typedef TUPLELIST TABLE[TABLE_SIZE+1];

extern TUPLELIST create_new_tuple(char** input, int key, int size);
extern TUPLELIST create_new_last_tuple(char** input, int key, int size, int tableSize);
extern void print_tuple(TUPLELIST temp);
extern void print_table(TABLE db);
extern void print_table_full(TABLE db);
extern int get_key(TABLE db);
extern int get_size(TABLE db);
extern int get_tablesize(TABLE db);
extern int hash(char* str);
extern void insert(TUPLELIST tuple, TABLE db);
extern bool check_duplicate(TUPLELIST tuple, TABLE db);
extern bool check_duplicate_bucket(TUPLELIST tuple, TUPLELIST bucket);
extern bool compare(TUPLELIST a, TUPLELIST b);
extern void delete_tuple(TUPLELIST tuple, TABLE db);
extern TUPLELIST delete_bucket(TUPLELIST tuple, TUPLELIST bucket, TABLE db);
extern bool search_unmatch(TUPLELIST tuple, TUPLELIST bucket);
extern void lookup(TUPLELIST tuple, TABLE db);
extern void lookup_bucket(TUPLELIST tuple, TUPLELIST bucket);
extern char* get_data_by_index(int index, TABLE db);
extern char** get_data(TABLE db);
extern TUPLELIST get_copy(TUPLELIST tuple);
extern TUPLELIST get_last_tuple(TABLE db);
extern TUPLELIST union_tuple(TUPLELIST a, TUPLELIST b, int attr1, int attr2);
extern void free_tuple(TUPLELIST tuple);
extern void free_table(TABLE db);

#endif 