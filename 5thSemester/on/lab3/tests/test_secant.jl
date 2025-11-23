# Michał Waluś 279695

include("../secant.jl")

using Test

@testset "Secant Method Tests" begin
    delta = 1e-5
    epsilon = 1e-5
    maxit = 128

    f(x) = x^2 - 4
    x0 = 0.0
    x1 = 5.0
    root, f_root, iterations, status = msiecznych(f, x0, x1, delta, epsilon, maxit)

    @test abs(root - 2.0) < delta || abs(f_root) < epsilon
    @test status == 0

    g(x) = sin(x) + 1.1
    root, f_root, iterations, status = msiecznych(g, x0, x1, delta, epsilon, maxit)
    @test status == 1

    f1(x) = sin(x)
    x0 = 3.0
    x1 = 4.0
    root, f_root, iterations, status = msiecznych(f1, x0, x1, delta, epsilon, maxit)
    @test abs(root - pi) < delta || abs(f_root) < epsilon
    @test status == 0
end