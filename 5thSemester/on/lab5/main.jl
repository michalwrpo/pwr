# Michał Waluś 279695

include("blocksys.jl")
using .blocksys

path = "examples/"


A = read_matrix(path * "A.txt")
# b = read_b_vector(path * "b.txt")

b = mult_by_1_vector(A)

# LU_simple(A)
# x = solve_LU_simple(A, b)

D = LU_choice(A)
x = solve_LU_choice(A, D, b)

# x = elimination_choice(A, b)
# x = elimination_simple(A, b)

x_exact = x_vector(A.n)
err = relative_error(x, x_exact)
println("Relative error: ", err)

# println(b)

# v = div(A.n, A.l)

# for i in 1:v
#     println("Block A_$i:")
#     for j in 1:A.l
#         for k in 1:A.l
#             print(A.An[i][j, k], " ")
#         end
#         println()
#     end
#     println()
# end

# println("Vector Bnh:")
# println(A.Bnh)
# println()
# println("Vector Bnv:")
# println(A.Bnv)
# println()

# println("Matrix Cn:")
# println(A.Cn)