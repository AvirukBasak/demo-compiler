#include "../include/floatmap.h"
#include <stdlib.h>
#include <stdbool.h>

FloatMap new_floatMap()
{
    FloatMap m = malloc(sizeof(struct FloatMap_T));
    if (!m) abort();
    m->keys = NULL;
    m->values = NULL;
    m->length = 0;
    return m;
}

void floatMap_set(FloatMap m, KeyType key, double value)
{
    if (!m) abort();
    size_t index = floatMap_findKey(m, key);
    if (index < m->length) {
        m->values[index] = value;
        return;
    }
    m->keys = realloc(m->keys, sizeof(KeyType) * (m->length +1));
    m->keys[m->length] = key;
    m->values = realloc(m->values, sizeof(double) * (m->length +1));
    m->values[m->length] = value;
    m->length++;
}

size_t floatMap_findKey(FloatMap m, KeyType key)
{
    if (!m) abort();
    KeyType i;
    for (i = 0; i < m->length; i++) {
        if (key == m->keys[i]) {
            return i;
        }
    }
    return m->length +1;
}

double floatMap_get(FloatMap m, KeyType key, bool *found)
{
    if (!m) abort();
    size_t index =  floatMap_findKey(m, key);
    if (index < m->length) {
        *found = true;
        return m->values[index];
    }
    *found = false;
    return 0;
}

void floatMap_free(FloatMap *m)
{
    if (!m || !*m) return;
    FloatMap map = *m;
    if (map->keys) free(map->keys);
    if (map->values) free(map->values);
    if (map) free(map);
    *m = NULL;
}
