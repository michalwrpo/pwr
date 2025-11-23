# Michał Waluś 279695

include("bisections.jl")
include("newtons.jl")
include("secant.jl")

f1(x) = exp(1-x) - 1
pf1(x) = -exp(1-x)

f2(x) = x*exp(-x)
pf2(x) = exp(-x) - x*exp(-x)

a = 0.0
b = 2.0
delta = 1e-5
epsilon = 1e-5
maxit = 4096

println("Funkcja 1: exp(1-x) - 1\n")

root_bisect, f_root_bisect, iterations_bisect, status_bisect = mbisekcji(f1, a, b, delta, epsilon)
println("Metoda bisekcji:")
println("pierwiastek: ", root_bisect)
println("f(pierwiastek): ", f_root_bisect)
println("iteracje: ", iterations_bisect)

x0 = 7.575

root_newton, f_root_newton, iterations_newton, status_newton = mstycznych(f1, pf1, x0, delta, epsilon, maxit)
println("\nMetoda Newtona:")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)

x0 = 0.0
x1 = 2.0

root_secant, f_root_secant, iterations_secant, status_secant = msiecznych(f1, x0, x1, delta, epsilon, maxit)
println("\nMetoda siecznych:")
println("pierwiastek: ", root_secant)
println("f(pierwiastek): ", f_root_secant)
println("iteracje: ", iterations_secant)

println("\n\nFunkcja 2: x*exp(-x)\n")

a = -1.0
b = 1.0

root_bisect, f_root_bisect, iterations_bisect, status_bisect = mbisekcji(f2, a, b, delta, epsilon)
println("Metoda bisekcji:")
println("pierwiastek: ", root_bisect)
println("f(pierwiastek): ", f_root_bisect)
println("iteracje: ", iterations_bisect)

x0 = -1.0

root_newton, f_root_newton, iterations_newton, status_newton = mstycznych(f2, pf2, x0, delta, epsilon, maxit)
println("\nMetoda Newtona:")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)

x0 = -1.0
x1 = 1.0

root_secant, f_root_secant, iterations_secant, status_secant = msiecznych(f2, x0, x1, delta, epsilon, maxit)
println("\nMetoda siecznych:")
println("pierwiastek: ", root_secant)
println("f(pierwiastek): ", f_root_secant)
println("iteracje: ", iterations_secant)