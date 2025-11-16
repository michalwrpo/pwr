%{
    int yywrap();
%}
%%

'''(''?[^']+)*'''               printf("%s", yytext);
\"\"\"(\"\"?[^\"]+)*\"\"\"      printf("%s", yytext);

'([^'\\]|\\\\|\\')*'            printf("%s", yytext);
\"([^\"\\]|\\\\|\\\")*\"        printf("%s", yytext);

#.*

%%
int yywrap() {
    printf("\n");
    return 1;
}

int main() {
    return yylex();
}
