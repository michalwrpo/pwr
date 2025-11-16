%{
    int yywrap();
    int docs = 0;
%}

%s DOCS
%x INCLUDE
%x STRING

%%
"#include \<"       { BEGIN(INCLUDE); printf("%s", yytext); }
<INCLUDE>[^\>]*     printf("%s", yytext);
<INCLUDE>\>         { 
                        if (docs) {
                            BEGIN(DOCS);
                        } else {
                            BEGIN(INITIAL);
                        }
                        printf("%s", yytext); 
                    }      

<DOCS>\/(\\\n)*\/(\\\n)*\/(.|\\\n)*      printf("%s", yytext);
<DOCS>\/(\\\n)*\/(\\\n)*!(.|\\\n)*      printf("%s", yytext);

<DOCS>\/(\\\n)*\*(\\\n)*\*(\*?[^\/\*]+\/?)*\*\/   printf("%s", yytext);
<DOCS>\/(\\\n)*\*(\\\n)*!(\*?[^\/\*]+\/?)*\*\/   printf("%s", yytext);

\"                  { BEGIN(STRING); printf("%s", yytext); }
<STRING>([^\"\\]|\\\\|\\\")*       printf("%s", yytext);
<STRING>\"          { 
                        if (docs) {
                            BEGIN(DOCS);
                        } else {
                            BEGIN(INITIAL);
                        }
                        printf("%s", yytext); 
                    }

\/(\\\n)*\/(.|\\\n)*
\/(\\\n)*\*(\*?[^\/\*]+\/?)*\*\/   printf(" ");

%%
int yywrap() {
    printf("\n");
    return 1;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        BEGIN(DOCS);
        docs = 1;
    }
    return yylex();
}
