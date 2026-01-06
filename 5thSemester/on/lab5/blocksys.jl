# Michał Waluś 279695

module blocksys
export A_Matrix, read_matrix, read_b_vector, elimination_simple, elimination_choice, mult_by_1_vector, x_vector, relative_error
export LU_simple, solve_LU_simple, LU_choice, solve_LU_choice

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

end