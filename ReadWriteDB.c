#include "ReadWriteDB.h"
#define MAX_ARG_LENGTH 50

extern void read(char* filename, TABLE db) {
    FILE *file = fopen(filename, "r");
    char str[MAX_ARG_LENGTH];
    char *cut;
    int key;
    int size;
    int tableSize;

    fgets(str,MAX_ARG_LENGTH, file);
    cut = strtok (str," ");
    key = atoi(cut);
    size = atoi(strtok (NULL," "));
    tableSize = atoi(strtok (NULL," "));
    
    char *attrInput[size];
    for(int i = 0; i < size; i++) {
        fgets(str,MAX_ARG_LENGTH, file);
        attrInput[i] = malloc(sizeof(str)-1);
        strcpy(attrInput[i], strtok(str, "\n"));
    }
    db[TABLE_SIZE] = create_new_last_tuple(attrInput, key, size, 0);
    fgets(str,MAX_ARG_LENGTH, file);

    for(int i = 0; i < tableSize; i++) {     
        char *tupleInput[size];
        for(int i = 0; i < size; i++) {
            fgets(str,MAX_ARG_LENGTH, file);
            cut = strtok(str, "\n");
            tupleInput[i] = malloc(sizeof(cut));
            strcpy(tupleInput[i], cut);
        }
        insert(create_new_tuple(tupleInput, key, size), db);
        fgets(str,MAX_ARG_LENGTH, file);
    }
    printf("Read.\n\n");
    fclose(file);
}

extern void write(char* filename, TABLE db) {
    FILE *file = fopen(filename, "w");
    fprintf(file, "%i %i %i\n", get_key(db),
                                get_size(db),
                                get_tablesize(db));

    for(int i = 0; i < get_size(db); i++) {
        fprintf(file, "%s\n", get_data_by_index(i, db));
    }
    fputs("\n", file);

    for(int i = 0; i < TABLE_SIZE; i++) {
        TUPLELIST bucket = db[i];
        while(bucket != NULL) {
            for(int k = 0; k < get_size(db); k++) {
                fprintf(file ,"%s\n", bucket->data[k]);
            }
            fputs("\n", file);
            bucket = bucket->next;
        }
    }
    printf("Written.\n\n");
    fclose(file);
}