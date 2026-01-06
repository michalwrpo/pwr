# Michał Waluś 279695

using LinearAlgebra

function relative_error(x::Vector{Float64}, x_exact::Vector{Float64})
    if length(x) != length(x_exact)
        error("Vectors must be of the same length to compute relative error.")
    end

    norm_diff = norm(x - x_exact)
    norm_exact = norm(x_exact)

    if norm_exact == 0.0
        error("Exact solution vector has zero norm, cannot compute relative error.")
    end

    return norm_diff / norm_exact
end