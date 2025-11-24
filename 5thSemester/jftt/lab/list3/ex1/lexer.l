%{
    #include "parser.tab.h"       /* brings in token definitions */
%}

%%
\n          return NL;

^#([^\n\\]|\\\n)*

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
"+"         return PLUS;
"-"         return MINUS;
"*"         return TIMES;
"/"         return DIVIDE;
"^"         return POWER;
"("         return LEFT;
")"         return RIGHT;

\\\n

[[:blank:]]+

. return ERR_INV_CHAR;

%%
