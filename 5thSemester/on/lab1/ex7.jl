# Michał Waluś 279695

function f(x::Float64)
    return sin(x) + cos(3*x)
end

function exactDerivative(x::Float64)
    return cos(x) - 3*sin(3 * x)
end

function approximation(x::Float64, h::Float64)
    return (f(x + h) - f(x)) / h 
end

x0 = Float64(1.0)

for n in 0:54 
    h = Float64(2^(-Float64(n)))
    exact = exactDerivative(x0)
    approx = approximation(x0, h)
    println("n=", n, ", h=", h, ", ~f'(x0)=", approx, ", f'(x0)=", exact, ", difference=", abs(exact - approx), ", 1+h=", 1 + h)
end