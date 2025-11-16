%{
    #include <stdio.h>
    int yywrap();
    int words = 0;
    int lines = 0;
%}
%%
^[[:blank:]]*\n                 
^[^\n[:blank:]]+            { printf("%s", yytext); words++; lines++; }
[^\n[:blank:]]+             { printf("%s", yytext); words++; }
^[[:blank:]]+               lines++;
[[:blank:]]+$
[[:blank:]]+                printf(" ");
\n                          { printf("\n"); }
%%
int yywrap() {
    printf("\n---\nLines: %d, Words: %d\n", lines, words);
    return 1;
}

int main() {
    return yylex();
}
