%{
    #define N 1234577
    #define Nexp 1234576
    
    #include <stdio.h>
    #include <stdint.h>

    int yylex(void);
    unsigned int ipow(unsigned int x, unsigned int y);
    void yyerror(const char *s);
    void output();
    void err(char* error);

    int mul_inv(int m, int n);
    int safe_mul(int x, int y, int mod);


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
                printf("Result: %d\n", $1);
            
            e = 0;
        }
    | expr symbol NL {
            if (!e)
                e = 1;
                printf("Error: Hanging operator.\n");
            
            output(); 
            e = 0;
        }
    | ERR_INV_CHAR NL       { printf("Error: Unrecognized symbol.\n"); e = 1; output(); }
    | ERR_OPS NL            { printf("Error: Too many operators.\n"); e = 1; output(); }
    | ERR_NUMS NL           { printf("Error: Too many numbers.\n"); e = 1; output(); }
    | error NL              { printf("Syntax error.\n"); e = 1; output(); }
    ;

expr:
      expr PLUS expr   { $$ = ($1 + $3) % N; symStack[stop++] = '+'; }
    | expr MINUS expr  { $$ = ($1 - $3 + N) % N; symStack[stop++] = '-'; }
    | expr TIMES expr  { $$ = safe_mul($1, $3, N); symStack[stop++] = '*'; }
    | expr DIVIDE expr { 
            if ($3 == 0) {
                $$ = 0;
                if (!e) {
                    printf("Error: Division by zero.\n");
                    e = 2;
                }
            } else {
                $$ = safe_mul($1, (mul_inv($3, N) + N) % N, N);
            }
            symStack[stop++] = '/'; 
        }
    | expr POWER expr-no-exp  { 
            $$ = ipow($1, $3); 
            symStack[stop++] = '^';
        }
    | LEFT expr RIGHT   { $$ = $2; }
    | NUMBER            { $$ = ($1 + N) % N; numStack[ntop++] = ($1 + N) % N; symStack[stop++] = 128; }
    | MINUS NUMBER      { $$ = (-$2 + N) % N; numStack[ntop++] = (-$2 + N) % N; symStack[stop++] = 128; }
    ;

expr-no-exp:
      expr-no-exp PLUS expr-no-exp   { $$ = ($1 + $3) % Nexp; symStack[stop++] = '+'; }
    | expr-no-exp MINUS expr-no-exp  { $$ = ($1 - $3 + Nexp) % Nexp; symStack[stop++] = '-'; }
    | expr-no-exp TIMES expr-no-exp  { $$ = safe_mul($1, $3, Nexp); symStack[stop++] = '*'; }
    | expr-no-exp DIVIDE expr-no-exp { 
            if ($3 == 0) {
                $$ = 0;
                if (!e) {
                    printf("Error: Division by zero.\n");
                    e = 2;
                }
                symStack[stop++] = '/'; 
            } else if ($3 % 2 == 0 || $3 % 7 == 0 || $3 % 73 == 0 || $3 % 151 == 0) {
                $$ = 0;
                if (!e) {
                    printf("Error: Number non-invertible.\n");
                    e = 1;
                }
            } else {
                $$ = safe_mul($1, (mul_inv($3, Nexp) + Nexp) % Nexp, Nexp); 
                symStack[stop++] = '/'; 
            }
        }
    | expr-no-exp POWER expr-no-exp  { 
            $$ = 0;
            if (!e) {
                printf("Error: Exponentation inside exponentiation.\n");
                e = 1;
            }        
        }
    | LEFT expr-no-exp RIGHT    { $$ = $2; }
    | NUMBER            { $$ = ($1 + Nexp) % Nexp; numStack[ntop++] = ($1 + Nexp) % Nexp; symStack[stop++] = 128; }
    | MINUS NUMBER      { $$ = (-$2 + Nexp) % Nexp; numStack[ntop++] = (-$2 + Nexp) % Nexp; symStack[stop++] = 128; }
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

int safe_mul(int x, int y, int mod) {
    uint64_t r = x;
    r *= y;
    return r % mod;
}

int mul_inv(int m, int n) {
	int a = m, b = n;
    int x = 1, y = 0;
    int r = 0, s = 1;
    while (b > 0) {
        int remainder = a % b;
        int quotient = a / b;
        a = b;
        b = remainder;
        int rr = r;
        int ss = s;
        r = x - quotient * r;
        s = y - quotient * s;
        x = rr;
        y = ss;
    }
    return x;
}

void output() {
    if (!e || e == 2) {
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
        printf("\n");
    }
    stop = 0;
    ntop = 0;
}

unsigned int ipow(unsigned int base, unsigned int exp) {
    uint64_t b = base % N;
    uint64_t result = 1;

    while (exp > 0) {
        if (exp & 1)
            result = ( result * b ) % N;

        b = ( b * b ) % N;
        exp >>= 1;
    }

    return result;
}

int main(void) {
    return yyparse();
}

void yyerror(const char *s) {
    // fprintf(stderr, "Parse error: %s\n", s);
}
