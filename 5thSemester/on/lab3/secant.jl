# Michał Waluś 279695

# f - funkcja, dla której szukamy pierwiastka
# x0, x1 - dwa punkty startowe
# delta, epsilon - dokładności obliczeń
# maxit - maksymalna liczba iteracji
function msiecznych(f, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64, maxit::Int)
    a = x0 # początek przedziału
    b = x1 # koniec przedziału
    
    fa = f(a) # wartość funkcji w a
    fb = f(b)   # wartość funkcji w b
    for k in 1:maxit
        if (abs(fa) > abs(fb))
            a, b = b, a
            fa, fb = fb, fa
        end
        s = (b - a) / (fb - fa) 
        b = a
        fb = fa
        a = a - fa * s
        fa = f(a)
        if (abs(a - b) < delta || abs(fa) < epsilon)
            return (a, fa, k, 0)
        end
    end

    return (a, fa, maxit, 1)    
end