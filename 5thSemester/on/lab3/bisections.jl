# Michał Waluś 279695

# f - funkcja, dla której szukamy pierwiastka
# a, b - końce przedziału
# delta, epsilon - dokładności obliczeń
function mbisekcji(f, a::Float64, b::Float64, delta::Float64, epsilon::Float64) 
    maxIter = 1024
    
    u = f(a)  # u - wartość funkcji w a
    v = f(b)  # v - wartość funkcji w b
    e = b - a # e - długość przedziału
    c = a     # c - środek przedziału
    w = v     # w - wartość funkcji w c

    if (sign(u) == sign(v))
        return (0.0, 0.0, 0, 1) 
    end
    
    for i in 1:maxIter 
        e = e / 2
        c = a + e
        w = f(c)
        if (abs(e) < delta || abs(w) < epsilon)
            return (c, w, i, 0)
        end
        if (sign(w) == sign(u))
            a = c
            u = w
        else
            b = c
            v = w
        end
    end

    return (c, w, maxIter, 0)
end