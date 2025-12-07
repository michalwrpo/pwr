# Michał Waluś 279695

function naturalna(x::Vector{Float64}, fx::Vector{Float64})
    n = length(x)
    if n != length(fx)
        error("Vectors x and fx must have the same length.")
    end

    cur = zeros(Float64, n)
    copy!(cur, fx)

    for i in 1:n
        for j in n-1:-1:i
            cur[j] = cur[j] - x[j - i + 1] * cur[j + 1]
        end
    end

    return cur
end