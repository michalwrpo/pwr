# Michał Waluś 279695

struct A_Matrix{T}
    n   :: Int                  # size of the matrix
    l   :: Int                  # block size
    An  :: Vector{Matrix{T}}    # A_n matrices, An[k] is A_k, length v, each l x l
    Bn  :: Vector{Vector{T}}    # B_n matrices, Bn[k] is B_(k-1), each represented as Vector elements 1-l are first row, l-(2l-1) are last column, length (v-1) x (2l - 1)  
    Cn  :: Vector{Matrix{T}}    # C_n matrices, Cn[k] is C_k, length v - 1, each l x l, to simplify calculations
end

function read_matrix(filename::String)
    n, l = 0, 0
    An, Bn, Cn = nothing, nothing, nothing
    open(filename, "r") do file
        first = split(strip(readline(file)))
        n = parse(Int, first[1])
        l = parse(Int, first[2])
        v = div(n, l)

        An  = [zeros(Float64, l, l) for _ in 1:v]
        Bn =  [Vector{Float64}(undef, 2*l - 1) for _ in 1:(v-1)]
        Cn  = [zeros(Float64, l, l) for _ in 1:(v-1)]

        # zero out Cn matrices
        for i in 1:(v-1)
            for row in 1:l
                for col in 1:l
                    Cn[i][row, col] = 0.0
                end
            end
        end

        for line in eachline(file)
            data = split(strip(line))
            if length(data) < 3
                error("Invalid matrix entry: $line")
            end
            
            row = parse(Int, data[1])
            col = parse(Int, data[2])
            value = parse(Float64, data[3])

            block_r = div(row - 1, l) + 1 # which A_n block row suggest
            block_c = div(col - 1, l) + 1 # which A_n block column suggest
            local_r = mod(row - 1, l) + 1
            local_c = mod(col - 1, l) + 1

            if col == row + l 
                Cn[block_r][local_r, local_c] = value
            else
                if block_r == block_c  # same block - A_n
                    An[block_r][local_r, local_c] = value
                elseif block_c + 1 == block_r && local_r == 1 # Block to the bottom of diagonal, first cell - horizontal B
                    Bn[block_c][local_c] = value
                elseif block_c + 1 == block_r && local_c == l # Block to the left of diagonal, last cell - vertical B
                    Bn[block_c][l - 1 + local_r] = value
                else
                    error("Unexpected matrix structure at ($row, $col)")
                end
            end
        end
    end

    return A_Matrix(n, l, An, Bn, Cn)
end

function read_b_vector(filename::String)
    b_vector = Vector{Float64}()
    open(filename, "r") do file
        n = parse(Int, strip(readline(file)))
        for line in eachline(file)
            value = parse(Float64, strip(line))
            push!(b_vector, value)
        end
    end
    return b_vector
end

function x_vector(n::Int)
    x = Vector{Float64}(undef, n)
    for i in 1:n
        x[i] = 1.0
    end
    return x
end