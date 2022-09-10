#ifndef INTMAP_H
#define INTMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

typedef uint32_t KeyType;

typedef struct IntMap_T *IntMap;
typedef struct IntMap_T
{
    KeyType *keys;
    int64_t *values;
    size_t length;
} IntMap_T;

IntMap new_intMap();
void intMap_set(IntMap m, KeyType key, int64_t value);
size_t intMap_findKey(IntMap m, KeyType key);
int64_t intMap_get(IntMap m, KeyType key, bool *found);
void intMap_free(IntMap *m);

#endif
