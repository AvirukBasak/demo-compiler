/* simplest version of calculator */
%{
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <math.h>
    #include "../include/globalvars.h"
    #include "../include/miscfunc.h"
    #include "../include/intmap.h"
%}

/* declare tokens */
%token TYPE_INT
%token KEYWORD_PRINT KEYWORD_VAR
%token ALNUM
%token ASSIGN
%token NUMBER
%token OPEN_PARENTHESIS CLOSE_PARENTHESIS
%token ADD SUB MUL DIV MOD POW
%token EOL

%%

input:
| input KEYWORD_PRINT KEYWORD_VAR EOL { printf("variables = "); MapFunc(int, print, intVars); printf(">> "); }
| input KEYWORD_PRINT exp EOL         { printf("%d\n>> ", $3); }
| input assignment EOL                { printf(">> "); }
| input exp EOL                       { if (!errno) printf("%d\n", $2); printf(">> "); }
;

assignment:
| TYPE_INT ALNUM ASSIGN exp {
    MapFunc(int, set, intVars, $2, $4);
    $$ = $4;
}
| ALNUM ASSIGN exp {
    MapFunc(int, set, intVars, $1, $3);
    $$ = $3;
}
;

exp:
| exp ADD exp                             { $$ = $1 + $3; }
| exp SUB exp                             { $$ = $1 - $3; }
| term                                    { $$ = $1; }
;

term:
| OPEN_PARENTHESIS exp CLOSE_PARENTHESIS  { $$ = $2; }
| OPEN_PARENTHESIS term CLOSE_PARENTHESIS { $$ = $2; }
| term POW term                           { $$ = pow($1, $3); }
| term MUL term                           { $$ = $1 * $3; }
| term DIV term                           { $$ = $1 / $3; }
| term MOD term                           { $$ = $1 % $3; }
| NUMBER                                  { $$ = $1; }
| ALNUM {
    bool found;
    int temp = (int) MapFunc(int, get, intVars, $1, &found);
    size_t len = strlen(code.varname);
    if (code.varname[len -1] == '\n')
        code.varname[len -1] = 0;
    if (!found) {
        fprintf(stderr, "parser: line %d: undefined variable '%s'\n", yylineno, code.varname);
        errno = 1;
    } else $$ = temp;
}
;

%%

int yyerror(char *s)
{
    fprintf(stderr, "parser: line %d: %s\n", yylineno, s);
    return 0;
}
