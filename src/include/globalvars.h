#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "../include/intmap.h"
#include <inttypes.h>

extern int errno;
extern IntMap intVars;
extern int yylineno;
extern char *yytext;

typedef struct CodeInputInfo {
    enum {
        IN_INT,
        IN_FLOAT,
        IN_STRING
    } type;
    struct {
        int64_t in_int;
        double in_float;
        char *in_string;
    } data;
    char *varname;
} CodeInputInfo;

extern CodeInputInfo code;

#endif
