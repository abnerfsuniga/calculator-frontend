%option noyywrap nodefault yylineno
%{
# include "calculator.h"
# include "calculator.tab.h"
%}


%%
[ \t]                       ;
\n                          { return EOL; }

[0-9]+\.[0-9]+              { yylval.d = atof(yytext); return FLOAT; }
[0-9]+                      { yylval.d = atof(yytext); return INTEGER; }

"print"                     { return PRINT; }

[a-zA-Z_][a-zA-Z0-9]*       { yylval.name = yytext; return VARIABLE; }

"+"                         { return ADD; }
"-"                         { return SUB; }
"*"                         { return MUL; }
"/"                         { return DIV; }
"^"                         { return EXP; }
"="                         { return EQUAL; }
")"                         { return RIGHT; }
"("                         { return LEFT; }

.                           { printf("UNKNOWN CHAR %c\n", *yytext); }
%%