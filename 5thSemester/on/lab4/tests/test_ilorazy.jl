# Michał Waluś 279695

include("../ilorazy.jl")

using Test

@testset "Difference Quotient Tests" begin
    x = [3.0, 1.0, 5.0, 6.0]
    f = [1.0, -3.0, 2.0, 4.0]

    result = ilorazyRoznicowe(x, f)
    expected = [1.0, 2.0, -0.375, 7.0/40.0]  # Expected divided differences

    @test length(result) == length(expected)
    for i in eachindex(expected)
        @test isapprox(result[i], expected[i]; atol=1e-8)
    end

    x = [2.0, 3.0, 4.0, 5.0, 6.0, 7.0]
    f = [7.0, 10.0, 13.0, 16.0, 19.0, 22.0]

    result = ilorazyRoznicowe(x, f)
    expected = [7.0, 3.0, 0.0, 0.0, 0.0, 0.0]  # Expected divided differences

    @test length(result) == length(expected)
    for i in eachindex(expected)
        @test isapprox(result[i], expected[i]; atol=1e-8)
    end
end
