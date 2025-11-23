# Michał Waluś 279695

include("../bisections.jl")

using Test

@testset "Bisections Method Tests" begin
    delta = 1e-5
    epsilon = 1e-5

    f(x) = x^2 - 4
    a, b = 0.0, 5.0
    root, f_root, iterations, status = mbisekcji(f, a, b, delta, epsilon)

    @test abs(root - 2.0) < delta || abs(f_root) < epsilon
    @test status == 0

    g(x) = x - 6
    root, f_root, iterations, status = mbisekcji(g, a, b, delta, epsilon)
    @test status == 1

    f(x) = sin(x)
    a, b = -1.0, 1.0
    root, f_root, iterations, status = mbisekcji(f, a, b, delta, epsilon)

    @test abs(root - 0.0) < delta || abs(f_root) < epsilon
    @test status == 0

    a, b = 2.0, 4.0
    root, f_root, iterations, status = mbisekcji(f, a, b, delta, epsilon)

    @test abs(root - pi) < delta || abs(f_root) < epsilon
    @test status == 0
end