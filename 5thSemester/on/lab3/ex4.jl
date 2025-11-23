# Michał Waluś 279695

include("bisections.jl")
include("newtons.jl")
include("secant.jl")

f(x) = sin(x) - 0.25*x^2
pf(x) = cos(x) - 0.5*x

a = 1.5
b = 2.0
delta = 5e-6
epsilon = 5e-6

root_bisect, f_root_bisect, iterations_bisect, status_bisect = mbisekcji(f, a, b, delta, epsilon)
println("Metoda bisekcji:")
println("pierwiastek: ", root_bisect)
println("f(pierwiastek): ", f_root_bisect)
println("iteracje: ", iterations_bisect)
println("error: ", status_bisect)

x0 = 1.5
maxit = 4096

root_newton, f_root_newton, iterations_newton, status_newton = mstycznych(f, pf, x0, delta, epsilon, maxit)
println("\nMetoda Newtona:")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)
println("error: ", status_newton)

x0 = 1.0
x1 = 2.0

root_secant, f_root_secant, iterations_secant, status_secant = msiecznych(f, x0, x1, delta, epsilon, maxit)
println("\nMetoda siecznych:")
println("pierwiastek: ", root_secant)
println("f(pierwiastek): ", f_root_secant)
println("iteracje: ", iterations_secant)
println("error: ", status_secant)
