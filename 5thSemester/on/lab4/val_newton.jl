# Michał Waluś 279695

function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
    n = length(x)
    if n != length(fx)
        error("Vectors x and fx must have the same length.")
    end

    prev = 0.0
    ans = fx[n]

    for i in (n - 1):-1:1
        prev = ans
        ans = fx[i] + (t - x[i]) * prev
    end
        
    return ans
end