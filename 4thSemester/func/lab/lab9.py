import math

def f(x): 
    y = math.sin(x)
    return y*y + y + x

def f1(x):
    return (math.sin(x) + 0.5)**2 - 0.25 + x

def sum(n):
    s = 0
    for i in range(n+1):
        s += f(i)
    return s

def sumrec(n, s):
    s += f(n)
    if n == 0:
        return s
    sumrec(n-1, s)
