# Michał Waluś 279695

function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})
    n = length(x)
    if n != length(f)
        error("Vectors x and f must have the same length.")
    end

    cur = zeros(Float64, n)
    prev = zeros(Float64, n)

    for i in 1:n
        cur[1] = f[n - i + 1]
        for j in 2:i
            cur[j] = (cur[j - 1] - prev[j - 1]) / (x[n - i + 1] - x[n - i + j])
        end
        copy!(prev, cur)
    end

    return cur        
end
