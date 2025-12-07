# Michał Waluś 279695

function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
    n = length(x)
    if n != length(fx)
        error("Vectors x and fx must have the same length.")
    end

    b = zeros(Float64, n)
    b[n] = fx[n]

    for i in (n - 1):-1:1
        b[i] = fx[i] + (t - x[i]) * b[i + 1]
    end
        
    return b[1]
end