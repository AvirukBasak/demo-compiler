#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "../include/intmap.h"

extern IntMap intVars;
extern int yylineno;
extern char *yytext;

int yylex(void);
int yyerror(char *);

#endif
