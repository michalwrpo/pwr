%{
    int yywrap();
    int ipow(int x, int y);
    int top = 0, a, b;
    int stack[100];
%}

%x ERROR

%%

-?[0-9]+        stack[top++] = atoi(yytext);
[[:blank:]]+

\+          {
    if (top < 2) {
        BEGIN(ERROR);
        fprintf(stderr, "Error: Not enough arguments\n");
        top = 0;
    } else {
        a = stack[--top];
        b = stack[--top];
        stack[top++] = b + a;
    }
}

-          {
    if (top < 2) {
        BEGIN(ERROR);
        fprintf(stderr, "Error: Not enough arguments\n");
        top = 0;
    } else {
        a = stack[--top];
        b = stack[--top];
        stack[top++] = b - a;
    }
}

\*          {
    if (top < 2) {
        BEGIN(ERROR);
        fprintf(stderr, "Error: Not enough arguments\n");
        top = 0;
    } else {
        a = stack[--top];
        b = stack[--top];
        stack[top++] = b * a;
    }
}

\/          {
    if (top < 2) {
        BEGIN(ERROR);
        fprintf(stderr, "Error: Not enough arguments\n");
        top = 0;
    } else {
        a = stack[--top];
        b = stack[--top];
        stack[top++] = b / a;
    }
}

\%          {
    if (top < 2) {
        BEGIN(ERROR);
        fprintf(stderr, "Error: Not enough arguments\n");
        top = 0;
    } else {
        a = stack[--top];
        b = stack[--top];
        stack[top++] = b % a;
    }
}

\^          {
    if (top < 2) {
        BEGIN(ERROR);
        fprintf(stderr, "Error: Not enough arguments\n");
        top = 0;
    } else {
        a = stack[--top];
        b = stack[--top];
        stack[top++] = ipow(b, a);
    }
}

\n      {
    if (top > 1) {
        fprintf(stderr, "Error: Not enough operators\n");
        top = 0;
    } else if (top == 1) {
        printf("%d\n", stack[--top]);
    }
}

[^0-9\n-+*/%^]+ {
    BEGIN(ERROR);
    fprintf(stderr, "Error: Invalid symbol: \"%s\"\n", yytext);
    top = 0;
}

<ERROR>[^\n]+
<ERROR>\n       BEGIN(INITIAL);

%%
int ipow(int x, int y) {
    if (!y) return 1;
    x = (y % 2) ? x * ipow(x*x, y/2) : ipow(x*x, y/2);
    return x;
}

int yywrap() {
    printf("\n");
    return 1;
}

int main() {
    return yylex();
}
