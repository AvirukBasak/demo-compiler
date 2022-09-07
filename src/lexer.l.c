/* recognize tokens for the calculator and print them out */
%{
  #include "parser.h"
%}

%%
"+"    { return ADD; }
"-"    { return SUB; }
"*"    { return MUL; }
"/"    { return DIV; }
"|"    { return ABS; }
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
\n     { return EOL; }
[ \t]  { /* ignore whitespace */ }
.      { printf("Mystery character %c\n", *yytext); }
%%

int yywrap() { return 1; }

int main(int argc, char **argv)
{
  int tok = yyparse();
  return 0;
}
