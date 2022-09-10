#ifndef MISCFUNC_H
#define MISCFUNC_H

// lexer functions

int yylex(void);
int yyerror(char *);

// user defined functions

int hash(const char *s);

#endif
