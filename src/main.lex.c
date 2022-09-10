/* recognize tokens for the calculator and print them out */
%{
    #include <string.h>
    #include "../include/globalvars.h"
    #include "../include/miscfunc.h"
    #include "../include/intmap.h"
    #include "parser.h"
%}

%%

"+"                    { return ADD; }
"-"                    { return SUB; }
"*"                    { return MUL; }
"/"                    { return DIV; }
"%"                    { return MOD; }
"="                    { return ASSIGN; }
[a-zA-Z_]+             { yylval = hash(yytext); return ALNUM; }
[0-9.]+                { yylval = atoi(yytext); return NUMBER; }
\n                     { yylineno++; return EOL; }
[ \t\f]                { /* ignore whitespace */ }
.                      { fprintf(stderr, "lexer: line %d: unexpected character '%c'\n", yylineno, *yytext); exit(1); }

%%

int yywrap() { return 1; }

int main(int argc, char **argv)
{
    intVars = new_intMap();
    int tok = yyparse();
    intMap_free(&intVars);
    return 0;
}
