#include "RelationalAlgebra.h"

void selection(char** category, char** data, int size, TABLE src, TABLE dst){
    int attribute[size];
    // printf("abd\n");
    for (int i = 0; i < size; i++){
        char** source = get_data(src);
        bool isFailed = true;
        // printf("abf\n");
        for (int j = 0; j < get_size(src); j++){
            // if (source[j] == NULL){
            //     printf("dmm\n");
            // } 
            // if (category[i] == NULL){
            //     printf("dcmm");
            // }
            // printf("abg\n");
            if (strcmp(source[j], category[i]) == 0){
                // printf("abc\n");
                attribute[i] = j+1;
                isFailed = false;
                // printf("abe\n");
                break;
            }
        }
        if (isFailed){
            printf("Selection failed.\n");
            return;
        }
    }

    TUPLELIST tuple = get_copy(get_last_tuple(src));
    dst[TABLE_SIZE] = tuple;
    // printf("abd\n");

    int key = get_key(src);
    for (int m = 0; m < size; m++){
        if (attribute[m] == key){
            dst[TABLE_SIZE]->key = key;
            int hashkey = hash(data[m]) % TABLE_SIZE;
            TUPLELIST temp = src[hashkey];
            if (temp == NULL) {return;}
            while (temp != NULL){
                if (compare_data(attribute, data, size, temp)){
                    TUPLELIST copy = get_copy(temp);
                    if (!check_duplicate(copy, dst)){
                        insert(copy, dst);
                    }    
                }
                temp = temp->next;
            }
            return;
        }
    }

    for (int n = 0; n < TABLE_SIZE; n++){
        TUPLELIST temp = src[n];
        while(temp != NULL){
            if (compare_data(attribute, data, size, temp)){
                // insert(get_copy(temp), dst);
                TUPLELIST copy = get_copy(temp);
                if (!check_duplicate(copy, dst)){
                    insert(copy, dst);
                }    
            }
            temp = temp->next;
        }
    }
}

bool compare_data(int* category, char** data, int size, TUPLELIST temp){
    for (int i = 0; i < size; i++){
        if (strcmp(temp->data[category[i]-1], data[i]) != 0){
            return false;
        }
    }
    return true;
}

void projection(int* category, int size, TABLE src, TABLE dst){
    char* attribute_array[size];
    for (int i = 0; i < size; i++){
        char* attribute = get_last_tuple(src)->data[category[i] - 1];
        attribute_array[i] = malloc(sizeof(char)*strlen(attribute));
        strcpy(attribute_array[i], attribute);
    }

    TUPLELIST tuple = create_new_last_tuple(attribute_array, 1, size, 0);
    dst[TABLE_SIZE] = tuple;

    for (int j = 0; j < TABLE_SIZE; j++){
        TUPLELIST bucket = src[j];
        while (bucket != NULL){
            char* input[size];
            for (int k = 0; k < size; k++){
                char* attribute = bucket->data[category[k] - 1];
                input[k] = malloc(sizeof(attribute));
                strcpy(input[k], attribute);
            }
            
            TUPLELIST temp = create_new_tuple(input, 1, size);
            if (!check_duplicate(temp,dst)){
                insert(temp,dst);
            }
            bucket = bucket->next;
        }
    } 
}

void join(int cat1, int cat2, TABLE src1, TABLE src2, TABLE dst){
    dst[TABLE_SIZE] = union_tuple(get_last_tuple(src1), get_last_tuple(src2), cat1, cat2);
    if (cat2 == get_key(src2)){
        for (int i = 0; i < TABLE_SIZE; i++){
            TUPLELIST temp = src1[i];
            while (temp != NULL){
                char* store = temp->data[cat1-1];
                int hashkey = hash(store) % TABLE_SIZE;
                TUPLELIST temp2 = src2[hashkey];
                while (temp2 != NULL){
                    if (strcmp(store, temp2->data[cat2-1]) == 0){
                        TUPLELIST joined = union_tuple(temp, temp2, cat1, cat2);
                        insert(joined, dst);
                    }
                    temp2 = temp2->next;
                }
                temp = temp->next;
            }
        }
        return;
    }

    for (int j = 0; j < TABLE_SIZE; j++){
        TUPLELIST temp = src1[j];
        while (temp != NULL){
            for (int k = 0; k < TABLE_SIZE; k++){
                TUPLELIST temp2 = src2[k];
                while(temp2 != NULL){
                    if (strcmp(temp->data[cat1-1], temp2->data[cat2-1]) == 0){
                        TUPLELIST joined = union_tuple(temp, temp2, cat1, cat2);\
                        insert(joined, dst);
                    }
                    temp2 = temp2 -> next;
                }
            }
            temp = temp -> next;
        }
    }
}