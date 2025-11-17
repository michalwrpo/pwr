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
^[[:blank:]]*[+*/^()]([^\n]|\\\n)*     return ERR_OPS;
^([^#\n]([^\n]|\\\n)*)?[+\-*/^]([[:blank:]]|\\\n)*[+*/^]([^\n]|\\\n)*$   return ERR_OPS;

^([^#\n]([^\n]|\\\n)*)?[0-9]+([[:blank:]]|\\\n)+[0-9]+([^\n]|\\\n)*$   return ERR_NUMS;
^[^#\n]+[^0-9\n+\-*/^()\\[:blank:]]+[^\n]*$           return ERR_INV_CHAR;

%%
