#include "../include/intmap.h"
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

IntMap new_intMap()
{
    IntMap m = malloc(sizeof(struct IntMap_T));
    if (!m) abort();
    m->keys = NULL;
    m->values = NULL;
    m->length = 0;
    return m;
}

void intMap_set(IntMap m, KeyType key, int64_t value)
{
    if (!m) abort();
    size_t index = intMap_findKey(m, key);
    if (index < m->length) {
        m->values[index] = value;
        return;
    }
    m->keys = realloc(m->keys, sizeof(KeyType) * (m->length +1));
    m->keys[m->length] = key;
    m->values = realloc(m->values, sizeof(int64_t) * (m->length +1));
    m->values[m->length] = value;
    m->length++;
}

size_t intMap_findKey(IntMap m, KeyType key)
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

int64_t intMap_get(IntMap m, KeyType key, bool *found)
{
    if (!m) abort();
    size_t index =  intMap_findKey(m, key);
    if (index < m->length) {
        *found = true;
        return m->values[index];
    }
    *found = false;
    return 0;
}

void intMap_free(IntMap *m)
{
    if (!m || !*m) return;
    IntMap map = *m;
    if (map->keys) free(map->keys);
    if (map->values) free(map->values);
    if (map) free(map);
    *m = NULL;
}
