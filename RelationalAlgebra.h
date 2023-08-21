#ifndef RELATIONALALGEBRA_H
#define RELATIONALALGEBRA_H
#include "Database.h"
#include "ReadWriteDB.h"

extern void selection(char** category, char** data, int size, TABLE src, TABLE dest);
extern bool compare_data(int* category, char** data, int size, TUPLELIST temp);
extern void projection(int* category, int size, TABLE src, TABLE dest);
extern void join(int cat1, int cat2, TABLE src1, TABLE src2, TABLE dest);

#endif