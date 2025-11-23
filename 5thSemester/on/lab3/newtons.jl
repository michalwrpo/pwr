# Michał Waluś 279695

# f - funkcja, dla której szukamy pierwiastka
# pf - pochodna funkcji f
# x0 - punkt startowy
# delta, epsilon - dokładności obliczeń
# maxit - maksymalna liczba iteracji
function mstycznych(f, pf, x0::Float64, delta::Float64, epsilon::Float64, maxit::Int)
    min_deriv = 1e-18 # minimalna wartość pochodnej

    v = f(x0) # wartość funkcji w aktualnym punkcie
    x1 = x0   # następny punkt iteracji

    if (abs(pf(x0)) < min_deriv)
        return (x0, v, 0, 2)
    end

    if (abs(v) < epsilon)
        return (x0, v, 0, 0)
    end
    for k in 1:maxit
        x1 = x0 - v / pf(x0)
        v = f(x1)
        if (abs(x1 - x0) < delta || abs(v) < epsilon)
            return (x1, v, k, 0)
        end
        if (abs(pf(x1)) < min_deriv)
            return (x1, v, k, 2)
        end
        x0 = x1
    end

    return (x0, f(x0), maxit, 1)
end