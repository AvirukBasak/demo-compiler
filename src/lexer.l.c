/* recognize tokens for the calculator and print them out */
%{
    #include "parser.h"
    #include "map.h"
    extern Map variables;
%}

%%

"+"                    { return ADD; }
"-"                    { return SUB; }
"*"                    { return MUL; }
"/"                    { return DIV; }
"%"                    { return MOD; }
"="                    { return ASSIGN; }
[a-zA-Z_]+             { return ALNUM; }
[0-9.]+                { yylval = atoi(yytext); return NUMBER; }
\n                     { return EOL; }
[ \t\f]                { /* ignore whitespace */ }
.                      { fprintf(stderr, "lexer: line %d: unexpected character '%c'\n", yylineno, *yytext); exit(1); }

%%

Map variables;

int yywrap() { return 1; }

int main(int argc, char **argv)
{
    variables = new_map();
    int tok = yyparse();
    map_free(&variables);
    return 0;
}
