/* simplest version of calculator */
%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "map.h"
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
| input exp EOL     { printf("  %d\n", $2); }
;

exp:
| ALNUM ASSIGN NUMBER  { map_set(variables, yytext, $3); $$ = $3; }
| NUMBER MUL NUMBER { $$ = $1 * $3; }
| NUMBER DIV NUMBER { $$ = $1 / $3; }
| NUMBER MOD NUMBER { $$ = $1 % $3; }
| prod ADD prod     { $$ = $1 + $3; }
| prod SUB prod     { $$ = $1 - $3; }
| exp MUL exp       { $$ = $1 * $3; }
| exp DIV exp       { $$ = $1 / $3; }
| exp MOD exp       { $$ = $1 % $3; }
| NUMBER            { $$ = $1; }
;

prod:
| NUMBER MUL NUMBER { $$ = $1 * $3; }
| NUMBER DIV NUMBER { $$ = $1 / $3; }
| NUMBER MOD NUMBER { $$ = $1 % $3; }
| prod MUL prod     { $$ = $1 * $3; }
| prod DIV prod     { $$ = $1 / $3; }
| prod MOD prod     { $$ = $1 % $3; }
| NUMBER            { $$ = $1; }
;

%%

int yyerror(char *s)
{
    fprintf(stderr, "parser: line %d: %s\n", yylineno, s);
}
