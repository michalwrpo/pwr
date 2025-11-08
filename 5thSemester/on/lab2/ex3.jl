# Michał Waluś 279695

include("hilb.jl")
include("mathcond.jl")

function get_x(n::Int)
    if n < 1
        error("n should be a positive integer.")
    end
    return [1 for _ in 1:n]
end

function get_b(A::Array{<:Number, 2}, x::Vector{<:Number})
    return A * x
end

function solve_inv(A::Array{<:Number, 2}, b::Vector{<:Number})
    return inv(A) * b
end

function solve_gauss(A::Array{<:Number, 2}, b::Vector{<:Number})
    return A\b
end

function rel_error(x::Vector{<:Number}, x_comp::Vector{<:Number})
    return norm(x - x_comp) / norm(x)
end

logcs = [0, 1, 3, 7, 12, 16]
ns = [5, 10, 20]

println("Hilbert's Matrix")

println("Using Gaussian elimination:")

n_max = 20

for n in 1:n_max
    A = hilb(n)
    x = get_x(n)
    b = get_b(A, x)
    x_sol = solve_gauss(A, b)
    # println(n, x_sol)
    # println("Relative error: ", rel_error(x, x_sol))
    println(n, " ", rel_error(x, x_sol))
end

println("\nVia multiplication by inverse:")

for n in 1:n_max
    A = hilb(n)
    x = get_x(n)
    b = get_b(A, x)
    x_sol = solve_inv(A, b)
    # println(n, x_sol)
    # println("Relative error: ", rel_error(x, x_sol))   
    println(n, " ", rel_error(x, x_sol))
end

println("Random Matrix")

for n in ns
    for ex in logcs
        A = matcond(n, 10.0^ex)
        x = get_x(n)
        b = get_b(A, x)
        x_solG = solve_gauss(A, b)
        # println("G ", n, " c=", c, " ", x_solG)
        # println("Relative error: ", rel_error(x, x_solG))
        println("G ", n, " ", ex, " ", rel_error(x, x_solG))


        x_solI = solve_inv(A, b)
        # println("I ", n, " c=", c, " ", x_solI)
        # println("Relative error: ", rel_error(x, x_solI))   
        println("I ", n, " ", ex, " ", rel_error(x, x_solI))
    end
end
