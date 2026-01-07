# Michał Waluś 279695

module blocksys
export A_Matrix, read_matrix, read_b_vector, elimination_simple, elimination_choice, mult_by_1_vector, x_vector, relative_error
export LU_simple, solve_LU_simple, LU_choice, solve_LU_choice, save_vector, save_vector_err
export solve_Gauss, check_Gauss, solve_Gauss_choice, check_Gauss_choice, solve_LU, check_LU, solve_LU_pivot, check_LU_pivot

include("structure.jl")
include("gauss.jl")
include("error.jl")

function mult_by_1_vector(A::A_Matrix{Float64})
    n = A.n
    l = A.l
    v = div(n, l)
    result = Vector{Float64}(undef, n)

    for block in 1:v
        for local_row in 1:l
            global_row = (block - 1) * l + local_row
            sum = 0.0

            # A_n
            for local_col in 1:l
                sum += A.An[block][local_row, local_col]
            end

            # Bnh
            if block > 1 && local_row == 1
                for col in 1:l
                    sum += A.Bn[block - 1][col]
                end
            end

            # Bnv
            if block > 1 && local_row > 1
                sum += A.Bn[block - 1][(l-1) + local_row]
            end

            # Cn
            if block < v
                sum += A.Cn[block][local_row, local_row]
            end

            result[global_row] = sum
        end
    end

    return result
end

# Read A and b from file, solves the system using Gauss elimination without pivoting 
# Measures execution time of the algorithm only
function solve_Gauss(A_file::AbstractString, b_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = read_b_vector(b_file)

    time = @elapsed begin
        x = elimination_simple(A, b)
    end

    save_vector(out_file, x)
    
    return time
end

# Read A and b from file, solves the system using Gauss elimination with pivoting 
# Measures execution time of the algorithm only
function solve_Gauss_choice(A_file::AbstractString, b_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = read_b_vector(b_file)

    time = @elapsed begin
        x = elimination_choice(A, b)
    end

    save_vector(out_file, x)

    return time
end

# Read A and b from file, solves the system using LU without pivoting 
# Measures execution time of the algorithm only (Decomposition + Forward/Backward sub)
function solve_LU(A_file::AbstractString, b_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = read_b_vector(b_file)

    time = @elapsed begin
        LU_simple(A)
        x = solve_LU_simple(A, b)
    end

    save_vector(out_file, x)

    return time
end

# Read A and b from file, solves the system using LU with pivoting 
# Measures execution time of the algorithm only (Decomposition + Forward/Backward sub)
function solve_LU_pivot(A_file::AbstractString, b_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = read_b_vector(b_file)

    time = @elapsed begin
        (Dn, p) = LU_choice(A)
        x = solve_LU_choice(A, Dn, b, p)
    end

    save_vector(out_file, x)

    return time
end

# Read A from file, generates x and solves the system using Gauss elimination without pivoting 
# Measures execution time of solution calculation only
function check_Gauss(A_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = mult_by_1_vector(A) 

    time = @elapsed begin
        x = elimination_simple(A, b)
    end

    x_exact = x_vector(A.n)
    err = relative_error(x, x_exact)
    save_vector_err(out_file, x, err)

    return time
end

# Read A from file, generates x and solves the system using Gauss elimination with pivoting 
# Measures execution time of solution calculation only
function check_Gauss_choice(A_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = mult_by_1_vector(A)

    time = @elapsed begin
        x = elimination_choice(A, b)
    end

    x_exact = x_vector(A.n)
    err = relative_error(x, x_exact)
    save_vector_err(out_file, x, err)

    return time
end

# Read A from file, generates x and solves the system using LU without pivoting 
# Measures execution time of solution calculation only (Decomposition + Solver)
function check_LU(A_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = mult_by_1_vector(A)

    time = @elapsed begin
        LU_simple(A)
        x = solve_LU_simple(A, b)
    end

    x_exact = x_vector(A.n)
    err = relative_error(x, x_exact)
    save_vector_err(out_file, x, err)

    return time
end

# Read A from file, generates x and solves the system using LU with pivoting 
# Measures execution time of solution calculation only (Decomposition + Solver)
function check_LU_pivot(A_file::AbstractString, out_file::AbstractString)
    A = read_matrix(A_file)
    b = mult_by_1_vector(A)

    time = @elapsed begin
        (Dn, p) = LU_choice(A)
        x = solve_LU_choice(A, Dn, b, p)
    end

    x_exact = x_vector(A.n)
    err = relative_error(x, x_exact)
    save_vector_err(out_file, x, err)

    return time
end

end