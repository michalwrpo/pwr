# Michał Waluś 279695

function mstycznych(f, pf, x0::Float64, delta::Float64, epsilon::Float64, maxit::Int)
    min_deriv = 1e-12

    v = f(x0)
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