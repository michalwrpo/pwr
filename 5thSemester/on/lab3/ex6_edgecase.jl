# Michał Waluś 279695

include("newtons.jl")

f1(x) = exp(1-x) - 1
pf1(x) = -exp(1-x)

f2(x) = x*exp(-x)
pf2(x) = exp(-x) - x*exp(-x)

delta = 1e-5
epsilon = 1e-5
maxit = 4096

x0 = 2.0

root_newton, f_root_newton, iterations_newton, status = mstycznych(f1, pf1, x0, delta, epsilon, maxit)
println("f1, x0 = 2.0:")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)
println("error: ", status)

x0 = 10.0

root_newton, f_root_newton, iterations_newton, status = mstycznych(f1, pf1, x0, delta, epsilon, maxit)
println("\nf1, x0 = ", x0, ":")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)
println("error: ", status)

x0 = 100.0

root_newton, f_root_newton, iterations_newton, status = mstycznych(f1, pf1, x0, delta, epsilon, maxit)
println("\nf1, x0 = ", x0, ":")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)
println("error: ", status)

x0 = 1.0

root_newton, f_root_newton, iterations_newton, status = mstycznych(f2, pf2, x0, delta, epsilon, maxit)
println("\nf2, x0 = 1.0:")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)
println("error: ", status)

x0 = 2.0

root_newton, f_root_newton, iterations_newton, status = mstycznych(f2, pf2, x0, delta, epsilon, maxit)
println("\nf2, x0 = 2.0:")
println("pierwiastek: ", root_newton)
println("f(pierwiastek): ", f_root_newton)
println("iteracje: ", iterations_newton)
println("error: ", status)