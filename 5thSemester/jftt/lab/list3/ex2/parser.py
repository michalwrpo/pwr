import ply.lex as lex
import ply.yacc as yacc

N = 1234577

numStack = []
symStack = []
e = False  # error flag


tokens = (
    'NUMBER',
    'ERR_INV_CHAR',
    'ERR_OPS',
    'ERR_NUMS',
    'NL',
    'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'POWER',
    'LEFT', 'RIGHT',
)

def t_ERR_OPS(t):
    r'^[\t ]*[+\-*/^()]([^\n]|\\\n)*|([^#\n]([^\n]|\\\n)*)?[+\-*/^()]([\t ]|\\\n)*[+\-*/^()]([^\n]|\\\n)*$'
    return t

t_PLUS   = r'\+'
t_MINUS  = r'-'
t_TIMES  = r'\*'
t_DIVIDE = r'/'
t_POWER  = r'\^'
t_LEFT   = r'\('
t_RIGHT  = r'\)'
t_ignore = ' \t'

def t_NL(t):
    r'\n'
    return t

def t_ERR_NUMS(t):
    r'([^#\n]([^\n]|\\\n)*)?[0-9]([\t ]|\\\n)*[0-9]([^\n]|\\\n)*$'
    return t

def t_NUMBER(t):
    r'-?\d+'
    t.value = int(t.value)
    return t

def t_ERR_INV_CHAR(t):
    r'[^#\n]+[^0-9\n+\-*/^()\\ \t]+[^\n]*$'
    return t

def t_error(t):
    t.type = 'ERR_INV_CHAR'
    t.lexer.skip(1)
    return t

lexer = lex.lex()

def output():
    global numStack, symStack, e
    if not e:
        j = 0
        for c in symStack:
            if c == 128:       # special "number marker"
                if j >= len(numStack):
                    print("Error: Too many operators")
                    break
                print(numStack[j], end=" ")
                j += 1
            else:
                print(chr(c), end=" ")
    print()
    numStack = []
    symStack = []


precedence = (
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE'),
    ('right', 'POWER'),
    ('nonassoc', 'LEFT', 'RIGHT'),
)

start = 'input'

def p_input_empty(p):
    "input : "
    pass

def p_input_lines(p):
    "input : input line"
    pass


def p_line_nl(p):
    "line : NL"
    pass


def p_line_expr_nl(p):
    "line : expr NL"
    global e
    output()
    if not e:
        print(f"Result: {p[1]}")
    e = 0


def p_line_hanging(p):
    "line : expr symbol NL"
    global e
    if not e:
        e = 1
        print("Error: Hanging operator.")
    output()
    e = 0


def p_line_err_inv(p):
    "line : ERR_INV_CHAR NL"
    print("Error: Unrecognized symbol.")

def p_line_err_ops(p):
    "line : ERR_OPS NL"
    print("Error: Too many operators.")

def p_line_err_nums(p):
    "line : ERR_NUMS NL"
    print("Error: Too many numbers.")


def p_expr_plus(p):
    "expr : expr PLUS expr"
    symStack.append(ord('+'))
    p[0] = (p[1] + p[3]) % N

def p_expr_minus(p):
    "expr : expr MINUS expr"
    symStack.append(ord('-'))
    p[0] = (p[1] - p[3]) % N

def p_expr_times(p):
    "expr : expr TIMES expr"
    symStack.append(ord('*'))
    p[0] = (p[1] * p[3]) % N

def p_expr_divide(p):
    "expr : expr DIVIDE expr"
    global e
    if p[3] == 0:
        if not e:
            print("Error: Division by zero.")
            e = 1
        p[0] = 0
    else:
        symStack.append(ord('/'))
        p[0] = (p[1] * pow(p[3], N - 2, N)) % N


def p_expr_power(p):
    "expr : expr POWER NUMBER"
    symStack.append(128)
    symStack.append(ord('^'))
    numStack.append((p[3] + N) % N)
    p[0] = pow(p[1], p[3], N)


def p_expr_parens(p):
    "expr : LEFT expr RIGHT"
    p[0] = p[2]


def p_expr_number(p):
    "expr : NUMBER"
    symStack.append(128)
    numStack.append((p[1] + N) % N)
    p[0] = (p[1] + N) % N


def p_symbol(p):
    """symbol : PLUS
              | MINUS
              | TIMES
              | DIVIDE
              | POWER
              | LEFT
              | RIGHT"""
    p[0] = p[1]


def p_error(p):
    if p:
        print("Parse error at token:", p.type)
    else:
        print("Parse error at EOF")


parser = yacc.yacc()

if __name__ == "__main__":
    import sys
    for line in sys.stdin:
        parser.parse(line)
