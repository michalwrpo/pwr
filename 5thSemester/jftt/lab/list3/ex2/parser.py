import ply.lex as lex
import ply.yacc as yacc

from fields import Z

N = 1234577

powRing = Z(N - 1)
GF = Z(N, powRing)

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

# def t_ERR_OPS(t):
#     r'^[\t ]*[+\-*/^()]([^\n]|\\\n)*|([^#\n]([^\n]|\\\n)*)?[+\-*/^()]([\t ]|\\\n)*[+\-*/^()]([^\n]|\\\n)*$'
#     return t

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

# def t_ERR_NUMS(t):
#     r'([^#\n]([^\n]|\\\n)*)?[0-9]([\t ]|\\\n)*[0-9]([^\n]|\\\n)*$'
#     return t

def t_NUMBER(t):
    r'\d+'
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
    if not e or e == 2:
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

def p_input_empty(_):
    "input : "
    pass

def p_input_lines(_):
    "input : input line"
    pass


def p_line_nl(_):
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


def p_line_err_inv(_):
    "line : ERR_INV_CHAR NL"
    print("Error: Unrecognized symbol.")

def p_line_err_ops(_):
    "line : ERR_OPS NL"
    print("Error: Too many operators.")

def p_line_err_nums(_):
    "line : ERR_NUMS NL"
    print("Error: Too many numbers.")

def p_line_err(_):
    "line : error NL"
    print("Syntax error.")


def p_expr_plus(p):
    "expr : expr PLUS expr"
    symStack.append(ord('+'))
    p[0] = GF.add(p[1], p[3])

def p_expr_minus(p):
    "expr : expr MINUS expr"
    symStack.append(ord('-'))
    p[0] = GF.sub(p[1], p[3])

def p_expr_times(p):
    "expr : expr TIMES expr"
    symStack.append(ord('*'))
    p[0] = GF.mul(p[1], p[3])

def p_expr_divide(p):
    "expr : expr DIVIDE expr"
    global e
    if p[3] == 0:
        if not e:
            print("Error: Division by zero.")
            e = 2
        p[0] = 0
    else:
        symStack.append(ord('/'))
        p[0] = GF.div(p[1], p[3])


def p_expr_power(p):
    "expr : expr POWER expr-no-exp"
    symStack.append(ord('^'))
    p[0] = GF.pow(p[1], p[3])


def p_expr_parens(p):
    "expr : LEFT expr RIGHT"
    p[0] = p[2]


def p_expr_number(p):
    "expr : NUMBER"
    symStack.append(128)
    numStack.append((p[1] + N) % N)
    p[0] = GF.num(p[1])

def p_expr_minus_number(p):
    "expr : MINUS NUMBER"
    symStack.append(128)
    numStack.append((-p[2] + N) % N)
    p[0] = GF.num(-p[2])

def p_expr_no_exp_plus(p):
    "expr-no-exp : expr-no-exp PLUS expr-no-exp"
    symStack.append(ord('+'))
    p[0] = powRing.add(p[1], p[3])

def p_expr_no_exp_minus(p):
    "expr-no-exp : expr-no-exp MINUS expr-no-exp"
    symStack.append(ord('-'))
    p[0] = powRing.sub(p[1], p[3])

def p_expr_no_exp_times(p):
    "expr-no-exp : expr-no-exp TIMES expr-no-exp"
    symStack.append(ord('*'))
    p[0] = powRing.mul(p[1], p[3])

def p_expr_no_exp_divide(p):
    "expr-no-exp : expr-no-exp DIVIDE expr-no-exp"
    global e
    if p[3] == 0:
        if not e:
            print("Error: Division by zero.")
            e = 2
        p[0] = 0
    else:
        try:
            symStack.append(ord('/'))
            p[0] = powRing.div(p[1], p[3])
        except ValueError:
            if not e:
                print("Error: Division not possible, inverse does not exist.")
                e = 2
            p[0] = 0


def p_expr_no_exp_power(p):
    "expr-no-exp : expr-no-exp POWER expr-no-exp"
    p[0] = 0
    if e == 0:
        print("Error: Exponentiation inside exponent is not allowed.")
        e = 2


def p_expr_no_exp_parens(p):
    "expr-no-exp : LEFT expr-no-exp RIGHT"
    p[0] = p[2]


def p_expr_no_exp_number(p):
    "expr-no-exp : NUMBER"
    symStack.append(128)
    numStack.append((p[1] + N) % N)
    p[0] = powRing.num(p[1]) 

def p_expr_no_exp_minus_number(p):
    "expr-no-exp : MINUS NUMBER"
    symStack.append(128)
    numStack.append((-p[2] + N) % N)
    p[0] = powRing.num(-p[2])


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
