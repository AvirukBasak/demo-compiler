#include "../include/miscfunc.h"
#include <stdlib.h>
#include <string.h>

int hash(const char *s)
{
    int hash = 0;
    size_t i, len = strlen(s);
    for (i = 0; i < len; i++) {
        hash += hash * 10 + (s[i] ^ hash);
    }
    return hash;
}
