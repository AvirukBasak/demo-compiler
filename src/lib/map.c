#ifndef MAP_C
#define MAP_C

#include <stdlib.h>
#include <stdbool.h>

#include "map.h"

Map new_map()
{
    Map m = malloc(sizeof(struct Map_T));
    if (!m) abort();
    m->keys = NULL;
    m->values = NULL;
    m->length = 0;
    return m;
}

void map_set(Map m, const int key, ValueType value)
{
    if (!m) abort();
    size_t index = map_findKey(m, key);
    if (index < m->length) {
        m->values[index] = value;
        return;
    }
    m->keys = realloc(m->keys, sizeof(int) * (m->length +1));
    m->keys[m->length] = key;
    m->values = realloc(m->values, sizeof(ValueType) * (m->length +1));
    m->values[m->length] = value;
    m->length++;
}

size_t map_findKey(Map m, const int key)
{
    if (!m) abort();
    int i;
    for (i = 0; i < m->length; i++) {
        if (key == m->keys[i]) {
            return i;
        }
    }
    return m->length +1;
}

ValueType map_get(Map m, const int key, bool *found)
{
    if (!m) abort();
    size_t index =  map_findKey(m, key);
    if (index < m->length) {
        *found = true;
        return m->values[index];
    }
    *found = false;
    return 0;
}

void map_free(Map *m)
{
    if (!m || !*m) return;
    Map map = *m;
    if (map->keys) free(map->keys);
    if (map->values) free(map->values);
    if (map) free(map);
    *m = NULL;
}

#else
    #error re-inclusion of map template

#endif
