#ifndef MAP_C
#define MAP_C

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "map.h"

typedef char *string;

Map new_map()
{
    Map m = malloc(sizeof(struct Map_T));
    if (!m) abort();
    m->keys = NULL;
    m->values = NULL;
    m->length = 0;
    return m;
}

void map_set(Map m, const string key, ValueType value)
{
    if (!m) abort();
    if (!key) abort();
    size_t index = map_findKey(m, key);
    if (index < m->length) {
        m->values[index] = value;
        return;
    }
    m->keys = (string *) realloc(m->keys, sizeof(string) * (m->length +1));
    m->keys[m->length] = (string) malloc(sizeof(char) * strlen(key) +1);
    strcpy(m->keys[m->length], key);
    m->values = (ValueType *) realloc(m->values, sizeof(ValueType) * (m->length +1));
    m->values[m->length] = value;
    m->length++;
}

size_t map_findKey(Map m, const string key)
{
    if (!m) abort();
    if (!key) abort();
    int i;
    for (i = 0; i < m->length; i++) {
        if (!strcmp(key, m->keys[i])) {
            return i;
        }
    }
    return m->length +1;
}

ValueType map_get(Map m, const string key, bool *found)
{
    if (!m) abort();
    if (!key) abort();
    size_t index =  map_findKey(m, key);
    if (index < m->length) {
        return m->values[index];
        *found = false;
    }
    *found = false;
    return 0;
}

void map_free(Map *m)
{
    if (!m || !*m) return;
    int i;
    Map map = *m;
    for (i = 0; i < map->length; i++) {
        if (map->keys[i]) free(map->keys[i]);
    }
    if (map->values) free(map->values);
    if (map) free(map);
    *m = NULL;
}

#else
    #error re-inclusion of map template

#endif
