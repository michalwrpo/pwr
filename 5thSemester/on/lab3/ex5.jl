# Michał Waluś 279695

include("bisections.jl")

f(x) = exp(x) - 3x

a = 0.0
b = 1.0
c = 2.0

delta = 1e-4
epsilon = 1e-4

root1, f_root1, iterations1, status1 = mbisekcji(f, a, b, delta, epsilon)

println("Pierwiastek w przedziale [", a, ", ", b, "]:")
println("pierwiastek: ", root1)
println("f(pierwiastek): ", f_root1)
println("iteracje: ", iterations1)
println("error: ", status1)

println("Wartość funkcji e^x: ", exp(root1))
println("Wartość funkcji 3x: ", 3*root1)

root2, f_root2, iterations2, status2 = mbisekcji(f, b, c, delta, epsilon)
println("\nPierwiastek w przedziale [", b, ", ", c, "]:")
println("pierwiastek: ", root2)
println("f(pierwiastek): ", f_root2)
println("iteracje: ", iterations2)
println("error: ", status2)

println("Wartość funkcji e^x: ", exp(root2))
println("Wartość funkcji 3x: ", 3*root2)
