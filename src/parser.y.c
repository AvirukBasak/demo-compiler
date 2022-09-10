/* simplest version of calculator */
%{
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>

    #include "../include/map.h"
    extern Map variables;

    extern int yylineno;
    extern char *yytext;
    int yylex(void);
    int yyerror(char *);

%}

/* declare tokens */
%token ALNUM
%token ASSIGN
%token NUMBER
%token ADD SUB MUL DIV MOD
%token EOL

%%

input:
| input assignment EOL { printf("%d\n", $2); }
| input exp EOL        { printf("%d\n", $2); }
;

assignment:
| ALNUM ASSIGN exp {
    map_set(variables, $1, $3);
    $$ = $3;
}
;

exp:
| exp ADD exp     { $$ = $1 + $3; }
| exp SUB exp     { $$ = $1 - $3; }
| term            { $$ = $1; }
;

term:
| term MUL term     { $$ = $1 * $3; }
| term DIV term     { $$ = $1 / $3; }
| term MOD term     { $$ = $1 % $3; }
| NUMBER            { $$ = $1; }
| ALNUM {
    bool found;
    $$ = map_get(variables, $1, &found);
    if (!found) {
        fprintf(stderr, "parser: line %d: undefined variable\n", yylineno);
        printf("assuming value = ");
        $$ = 0;
    }
}
;

%%

int yyerror(char *s)
{
    fprintf(stderr, "parser: line %d: %s\n", yylineno, s);
}
