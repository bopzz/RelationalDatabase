#include "Database.h"

TUPLELIST create_new_tuple(char **input, int key, int size)
{
    TUPLELIST tuple = malloc(sizeof(struct TUPLE));
    tuple->size = size;
    tuple->key = key;
    tuple->tableSize = 0;
    tuple->data = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        tuple->data[i] = (char *)malloc(sizeof(input[i]));
        strcpy(tuple->data[i], input[i]);
    }
    tuple->next = NULL;
    return tuple;
}

TUPLELIST create_new_last_tuple(char **input, int key, int size, int tableSize)
{
    TUPLELIST tuple = malloc(sizeof(struct TUPLE));
    tuple->size = size;
    tuple->key = key;
    tuple->tableSize = tableSize;
    tuple->data = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++)
    {
        tuple->data[i] = (char *)malloc(sizeof(input[i]));
        strcpy(tuple->data[i], input[i]);
    }
    tuple->next = NULL;
    return tuple;
}

void print_tuple(TUPLELIST tuple)
{
    for (int i = 0; i < tuple->size; i++)
    {
        printf("%s\t\t", tuple->data[i]);
    }
    printf("\n");
}

void print_table(TABLE db)
{
    print_tuple(db[TABLE_SIZE]);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        TUPLELIST temp = db[i];
        while (temp != NULL)
        {
            print_tuple(temp);
            temp = temp->next;
        }
    }
}

int get_key(TABLE db){
    return db[TABLE_SIZE]->key;
}

int get_size(TABLE db){
    return db[TABLE_SIZE]->size;
}

int get_tablesize(TABLE db){
    return db[TABLE_SIZE]->tableSize;
}

int hash(char *str)
{
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        res += str[i];
    }
    return res;
}

void insert(TUPLELIST tuple, TABLE db)
{
    if (check_duplicate(tuple, db))
    {
        printf("Data already exists.\n");
        return;
    }
    int hashkey = hash(tuple->data[tuple->key - 1]) % TABLE_SIZE;
    TUPLELIST temp = db[hashkey];
    db[TABLE_SIZE]->tableSize++;
    if (temp == NULL)
    {
        db[hashkey] = tuple;
        // print_tuple(tuple);
        return;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = tuple;
        // print_tuple(tuple);
    }
}

bool check_duplicate(TUPLELIST tuple, TABLE db)
{
    int hashkey = hash(tuple->data[tuple->key - 1]) % TABLE_SIZE;
    TUPLELIST check = db[hashkey];
    if (check == NULL)
    {
        return false;
    }
    return check_duplicate_bucket(tuple, check);
}

bool check_duplicate_bucket(TUPLELIST tuple, TUPLELIST bucket)
{
    while (bucket != NULL)
    {
        if (compare(tuple, bucket))
        {
            return true;
        }
        bucket = bucket->next;
    }
    return false;
}

bool compare(TUPLELIST a, TUPLELIST b)
{
    if (a->size != b->size)
    {
        return false;
    }

    for(int i = 0; i < a->size; i++){
        if (strcmp(a->data[i], b->data[i]) != 0){
            return false;
        }
    }
    return true;
}

void delete_tuple(TUPLELIST tuple, TABLE db){
    if (strcmp(tuple->data[tuple->key-1], "") != 0){
        int hashkey = hash(tuple->data[tuple->key - 1]) % TABLE_SIZE;
        TUPLELIST del = db[hashkey];
        if (del == NULL){
            printf("No such tuples.\n");
            return;
        }
        db[hashkey] = delete_bucket(tuple, del, db);
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++){
        db[i] = delete_bucket(tuple, db[i], db);
    }
}

TUPLELIST delete_bucket (TUPLELIST tuple, TUPLELIST bucket, TABLE db){
    TUPLELIST top = bucket;
    TUPLELIST temp = NULL;
    while (bucket != NULL){
        if (search_unmatch(tuple, bucket)){
            temp = bucket;
        } else if (temp == NULL){
            db[TABLE_SIZE]->tableSize--;
            top = bucket->next;
        } else {
            db[TABLE_SIZE]->tableSize--;
            temp->next = bucket->next;
        }
        bucket = bucket->next;
    }
    return top;
}

bool search_unmatch(TUPLELIST tuple, TUPLELIST bucket){
    for (int i = 0; i < bucket->size; i++){
        if ((strcmp(tuple->data[i], "") != 0) && (strcmp(tuple->data[i], bucket->data[i]) != 0)){
            return true;
        }
    }
    return false;
}

void lookup(TUPLELIST tuple, TABLE db) {
    if(strcmp(tuple->data[tuple->key-1], "") != 0) {
        int hashkey = hash(tuple->data[tuple->key-1]) % TABLE_SIZE;
        TUPLELIST temp = db[hashkey];
        if(temp == NULL) return;
        lookup_bucket(tuple, temp);
        return;
    }
    for(int i = 0; i < TABLE_SIZE; i++) {
        lookup_bucket(tuple, db[i]);
    }
}

void lookup_bucket(TUPLELIST tuple, TUPLELIST bucket){
    while (bucket != NULL){
        if (!search_unmatch(tuple, bucket)){
            print_tuple(bucket);
        }
        bucket = bucket->next;
    }
}

char* get_data_by_index(int index, TABLE db){
    return db[TABLE_SIZE]->data[index];
}

char** get_data(TABLE db){
    return db[TABLE_SIZE]->data;
}

TUPLELIST get_copy(TUPLELIST tuple){
    return create_new_tuple(tuple->data, tuple->key, tuple->size);
}

TUPLELIST get_last_tuple(TABLE db){
    return db[TABLE_SIZE];
}

void free_tuple(TUPLELIST tuple){
    if (tuple->next != NULL){
        free_tuple(tuple->next);
    }
    for (int i = 0; i < tuple->size; i++){
        free(tuple->data[i]);
    }
    free(tuple->data);
    free(tuple);
}

void free_table(TABLE db){
    for (int i = 0; i < TABLE_SIZE; i++){
        if (db[i] != NULL){
            free(db[i]);
        }
    }
    free(db[TABLE_SIZE]);
}

TUPLELIST union_tuple(TUPLELIST a, TUPLELIST b, int attr1, int attr2){
    bool isDuplicate = strcmp(a->data[attr1-1], b->data[attr2-1]) == 0;     
    int totalSize = a->size + b->size;
    if (isDuplicate){
        totalSize -= 1;
    } 
    char* attribute[totalSize];
    for (int i = 0; i < a->size; i++){
        char* data = a->data[i];
        attribute[i] = malloc(sizeof(char) * strlen(data));
        strcpy(attribute[i], data);
    }
    int check = 0;
    for (int i = 0; i < b->size; i++){
        if (i != attr2-1 || !isDuplicate){
            char* data = b->data[i];
            attribute[a->size + check] = malloc(sizeof(char) * strlen(data));
            strcpy(attribute[a->size + check], data);
            check++;
        }
    }
    return create_new_tuple(attribute, a->key, totalSize);
}