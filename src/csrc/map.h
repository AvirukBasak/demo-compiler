#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#if ! defined MAP_VALUE_TYPE || ! defined MAP_VALUE_FORMAT
    #undef MAP_MAP_VALUE_TYPE
    #undef MAP_MAP_VALUE_FORMAT
    #define MAP_VALUE_TYPE     int
    #define MAP_VALUE_FORMAT   "%d"
#endif

typedef MAP_VALUE_TYPE ValueType;
typedef struct Map_T *Map;
typedef struct Map_T
{
    int *keys;
    ValueType *values;
    size_t length;
} Map_T;

Map new_map();
void map_set(Map m, const int key, ValueType value);
size_t map_findKey(Map m, const int key);
ValueType map_get(Map m, const int key, bool *found);
void map_free(Map *m);

#endif
