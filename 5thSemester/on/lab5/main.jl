# Michał Waluś 279695

include("blocksys.jl")
using .blocksys

path = "examples/16/"


# A = read_matrix(path * "A.txt")
# # b = read_b_vector(path * "b.txt")

# b = mult_by_1_vector(A)

# # LU_simple(A)
# # x = solve_LU_simple(A, b)

# D, choice = LU_choice(A)
# x = solve_LU_choice(A, D, b, choice)

# # x = elimination_choice(A, b)
# # x = elimination_simple(A, b)

# x_exact = x_vector(A.n)
# err = relative_error(x, x_exact)
# println("Relative error: ", err)

solve_Gauss(path * "A.txt", path * "b.txt", "foo1.txt")
check_Gauss(path * "A.txt", "foo2.txt")
solve_Gauss_choice(path * "A.txt", path * "b.txt", "foo3.txt")
check_Gauss_choice(path * "A.txt", "foo4.txt")
solve_LU(path * "A.txt", path * "b.txt", "foo5.txt")
check_LU(path * "A.txt", "foo6.txt")
solve_LU_pivot(path * "A.txt", path * "b.txt", "foo7.txt")
check_LU_pivot(path * "A.txt", "foo8.txt")