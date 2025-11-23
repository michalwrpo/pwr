# Michał Waluś 279695

function mbisekcji(f, a::Float64, b::Float64, delta::Float64, epsilon::Float64) 
    maxIter = 1024
    
    u = f(a)
    v = f(b)
    e = b - a
    w = v

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