#ifndef FLOATMAP_H
#define FLOATMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

typedef uint32_t KeyType;

typedef struct FloatMap_T *FloatMap;
typedef struct FloatMap_T
{
    KeyType *keys;
    double *values;
    size_t length;
} FloatMap_T;

FloatMap new_floatMap();
void floatMap_set(FloatMap m, KeyType key, double value);
size_t floatMap_findKey(FloatMap m, KeyType key);
double floatMap_get(FloatMap m, KeyType key, bool *found);
void floatMap_free(FloatMap *m);

#endif
