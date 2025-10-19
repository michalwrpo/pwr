# Michał Waluś 279695

f(x::Float64) = Float64(sqrt(x^2 + 1) - 1)
g(x::Float64) = Float64(x^2 / (sqrt(x^2 + 1) + 1))

function compare(n::Int)
    for i in 1:n
        fVal = f(8^Float64(-i))
        gVal = g(8^Float64(-i))
        println("n=", i, ", f(x)=", fVal, ", g(x)=", gVal)
    end
end

compare(180)