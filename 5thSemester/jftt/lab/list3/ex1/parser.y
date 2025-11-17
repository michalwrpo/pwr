%{
    #define N 1234577
    
    #include <stdio.h>
    #include <stdint.h>

    int yylex(void);
    unsigned int ipow(unsigned int x, unsigned int y);
    void yyerror(const char *s);
    void output();
    void err(char* error);

    int numStack[100];
    char symStack[200];
    int ntop = 0, stop = 0, e = 0;
%}

%token NUMBER
%token ERR_INV_CHAR
%token ERR_OPS
%token ERR_NUMS
%token NL
%left PLUS MINUS
%left TIMES DIVIDE
%right POWER
%nonassoc LEFT RIGHT


%%
input:
    %empty
    | input line
    ;

line:
    NL 
    | expr NL   { 
            output(); 
            if (!e)
                printf("\nResult: %d\n", $1);
            
            e = 0;
        }
    | expr symbol NL {
            if (!e)
                e = 1;
                printf("Error: Hanging operator.\n");
            
            output(); 
            e = 0;
        }
    | ERR_INV_CHAR NL       { printf("Error: Unrecognized symbol.\n"); }
    | ERR_OPS NL            { printf("Error: Too many operators.\n"); }
    | ERR_NUMS NL           { printf("Error: Too many numbers.\n"); }
    ;

expr:
      expr PLUS expr   { $$ = ($1 + $3) % N; symStack[stop++] = '+'; }
    | expr MINUS expr  { $$ = ($1 - $3) % N; symStack[stop++] = '-'; }
    | expr TIMES expr  { $$ = ($1 * $3) % N; symStack[stop++] = '*'; }
    | expr DIVIDE expr { 
            if ($3 == 0) {
                $$ = 0;
                if (!e) {
                    printf("Error: Division by zero.\n");
                    e = 1;
                }
            } else {
                $$ = ($1 * ipow($3, N - 2)) % N; 
                symStack[stop++] = '/'; 
            }
        }
    | expr POWER NUMBER  { 
            $$ = ipow($1, $3); 
            numStack[ntop++] = ($3 + N) % N; 
            symStack[stop++] = 128;
            symStack[stop++] = '^';
        }
    | LEFT expr RIGHT
    | NUMBER            { $$ = ($1 + N) % N; numStack[ntop++] = ($1 + N) % N; symStack[stop++] = 128; }
    ;

symbol:
    PLUS
    | MINUS
    | TIMES
    | DIVIDE
    | POWER
    | LEFT
    | RIGHT
    ;

%%

void output() {
    if (!e) {
        int j = 0;
        unsigned char c;
        for (int i = 0; i < stop; i++) {
            c = symStack[i];
            if (c == 128) {
                if (j == ntop) {
                    printf("Error: Too many operators");
                    break;
                }
                printf("%d ", numStack[j++]);
            } else {
                printf("%c ", c);
            }
        }
    }
    stop = 0;
    ntop = 0;
}

unsigned int ipow(unsigned int base, unsigned int exp) {
    base %= N;
    unsigned int result = 1;

    while (exp > 0) {
        if (exp & 1)
            result = ( (uint64_t)result * base ) % N;

        base = ( (uint64_t)base * base ) % N;
        exp >>= 1;
    }

    return result;
}

int main(void) {
    return yyparse();
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
