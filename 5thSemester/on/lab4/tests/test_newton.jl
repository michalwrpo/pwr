# Michał Waluś 279695

include("../val_newton.jl")

using Test

@testset "Evaluation of polynomial in Newton form Tests" begin
    x = [3.0, 1.0, 5.0, 6.0]
    fx = [1.0, -3.0, 2.0, 4.0]
    t = 4.0

    result = warNewton(x, fx, t)
    expected = -8.0  # Expected value of the polynomial at t=4.0

    @test isapprox(result, expected; atol=1e-8)

    x = [2.0, 3.0, 4.0, 5.0, 6.0, 7.0]
    fx = [7.0, 10.0, 13.0, 16.0, 19.0, 22.0]
    t = 5.5

    result = warNewton(x, fx, t)
    expected = 418.25  # Expected value of the polynomial at t=5.5

    @test isapprox(result, expected; atol=1e-8)
end
