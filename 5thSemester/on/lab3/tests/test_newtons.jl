# Michał Waluś 279695

include("../newtons.jl")

using Test

@testset "Newton's Method Tests" begin
    delta = 1e-5
    epsilon = 1e-5
    maxit = 128

    f(x) = x^2 - 4
    df(x) = 2x
    x0 = 1.0
    root, f_root, iterations, status = mstycznych(f, df, x0, delta, epsilon, maxit)

    @test abs(root - 2.0) < delta || abs(f_root) < epsilon
    @test status == 0

    g(x) = sin(x) + 1.1
    dg(x) = cos(x)
    root, f_root, iterations, status = mstycznych(g, dg, x0, delta, epsilon, maxit)
    @test status == 1

    h(x) = x^2 - 4x + 5
    dh(x) = 2x - 4
    root, f_root, iterations, status = mstycznych(h, dh, x0, delta, epsilon, maxit)
    @test status == 2

    f1(x) = sin(x)
    df1(x) = cos(x)
    x0 = 3.0
    root, f_root, iterations, status = mstycznych(f1, df1, x0, delta, epsilon, maxit)

    @test abs(root - pi) < delta || abs(f_root) < epsilon
    @test status == 0
end
