#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#undef new

/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                    \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));              \
    if (!tmp) abort();                                                      \
    tmp;                                                                    \
})

#define Map(vtype) map_##vtype
#define MapFunc(vtype, func, ...) map_##vtype##_##func(__VA_ARGS__)

/**
 * Generates function prototype definitions and typedefs for the map
 */
#define MapDeclarePrototypes(vtype)                                         \
                                                                            \
typedef struct map_##vtype {                                                \
    unsigned long int key;                                                  \
    vtype value;                                                            \
    struct map_##vtype *prev;                                               \
    struct map_##vtype *next;                                               \
    struct map_##vtype *end;                                                \
} *map_##vtype;                                                             \
                                                                            \
map_##vtype map_##vtype##_newmap();                                         \
unsigned long int map_##vtype##_hashString(const char *strkey);             \
map_##vtype map_##vtype##_findKey(map_##vtype m, unsigned long int key);    \
vtype map_##vtype##_get(map_##vtype m, unsigned long int key, bool *found); \
bool map_##vtype##_set(map_##vtype m, unsigned long int key, vtype val);    \
bool map_##vtype##_del(map_##vtype m, unsigned long int key);               \
void map_##vtype##_print(map_##vtype m);                                    \
void map_##vtype##_free(map_##vtype *m);

/**
 * Defines the chosen map from template: generates the necessary function definitions
 * NOTE: requires MapDeclarePrototypes(vtype, vformat)
 */
#define MapDefine(vtype, vformat)                                           \
                                                                            \
map_##vtype map_##vtype##_newmap()                                          \
{                                                                           \
    map_##vtype m = new(map_##vtype);                                       \
    m->key = 0;                                                             \
    m->value = 0;                                                           \
    m->prev = NULL;                                                         \
    m->next = NULL;                                                         \
    m->end = m;                                                             \
    return m;                                                               \
}                                                                           \
                                                                            \
unsigned long int map_##vtype##_hashString(const char *strkey)              \
{                                                                           \
    unsigned long int hash = 0;                                             \
    size_t i, len = strlen(strkey);                                         \
    for (i = 0; i < len; i++) {                                             \
        hash = hash * 2 + (strkey[i] ^ hash);                               \
    }                                                                       \
    return hash;                                                            \
}                                                                           \
                                                                            \
map_##vtype map_##vtype##_findKey(map_##vtype m, unsigned long int key)     \
{                                                                           \
    if (!m) abort();                                                        \
    map_##vtype p = m->next;                                                \
    while (p != NULL) {                                                     \
        if (p->key == key) return p;                                        \
        p = p->next;                                                        \
    }                                                                       \
    return NULL;                                                            \
}                                                                           \
                                                                            \
vtype map_##vtype##_get(map_##vtype m, unsigned long int key, bool *found)  \
{                                                                           \
    if (!m) abort();                                                        \
    map_##vtype node = map_##vtype##_findKey(m, key);                       \
    if (!node) {                                                            \
        *found = false;                                                     \
        return 0;                                                           \
    }                                                                       \
    *found = true;                                                          \
    return node->value;                                                     \
}                                                                           \
                                                                            \
bool map_##vtype##_set(map_##vtype m, unsigned long int key, vtype val)     \
{                                                                           \
    if (!m) abort();                                                        \
    map_##vtype node = map_##vtype##_findKey(m, key);                       \
    if (node) {                                                             \
        node->value = val;                                                  \
    } else {                                                                \
        node = new(map_##vtype);                                            \
        node->key = key;                                                    \
        node->value = val;                                                  \
        node->prev = m->end;                                                \
        node->next = NULL;                                                  \
        node->end = NULL;                                                   \
        if (m->end) m->end->next = node;                                    \
        else m->next = node;                                                \
        m->end = node;                                                      \
    }                                                                       \
    return true;                                                            \
}                                                                           \
                                                                            \
bool map_##vtype##_del(map_##vtype m, unsigned long int key)                \
{                                                                           \
    if (!m) abort();                                                        \
    map_##vtype node = map_##vtype##_findKey(m, key);                       \
    if (!node) return false;                                                \
    map_##vtype tmp = node;                                                 \
    node = node->prev;                                                      \
    node->next = tmp->next;                                                 \
    tmp->next->prev = node;                                                 \
    free(tmp);                                                              \
    return true;                                                            \
}                                                                           \
                                                                            \
void map_##vtype##_print(map_##vtype m)                                     \
{                                                                           \
    if (!m) abort();                                                        \
    map_##vtype p = m->next;                                                \
    printf("{\n");                                                          \
    while (p != NULL) {                                                     \
        printf("    %lu" " => " vformat, p->key, p->value);                 \
        printf("\n");                                                       \
        p = p->next;                                                        \
    }                                                                       \
    printf("}\n");                                                          \
}                                                                           \
                                                                            \
void map_##vtype##_free(map_##vtype *m)                                     \
{                                                                           \
    if (!*m) abort();                                                       \
    map_##vtype p = *m;                                                     \
    while (p != NULL) {                                                     \
        map_##vtype tmp = p;                                                \
        p = p->next;                                                        \
        free(tmp);                                                          \
    }                                                                       \
    *m = NULL;                                                              \
}
