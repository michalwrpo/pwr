# Michał Waluś 279695

include("../naturalna.jl")

using Test

@testset "Natural Form Coefficients Tests" begin
    x = [0.0, 1.0, 2.0]
    fx = [1.0, 3.0, 2.0]

    result = naturalna(x, fx)
    expected = [1.0, 1.0, 2.0]  # Expected coefficients for the polynomial

    @test length(result) == length(expected)
    for i in eachindex(expected)
        @test isapprox(result[i], expected[i]; atol=1e-8)
    end

    x = [1.0, 2.0, 3.0, 4.0]
    fx = [2.0, 3.0, 5.0, 7.0]

    result = naturalna(x, fx)
    expected = [-33.0, 65.0, -37.0, 7.0]  # Expected coefficients for the polynomial

    @test length(result) == length(expected)
    for i in eachindex(expected)
        @test isapprox(result[i], expected[i]; atol=1e-8)
    end
end