#include <stdio.h>

extern int yylineno;
extern FILE *yyin;
extern int yylex();
extern int yyparse();

void yyerror(char *s, ...);
