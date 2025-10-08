# Michał Waluś 279695

function notequal(start::Float64)
    x = Float64(start)
    while Float64(x * Float64(1/x)) == Float64(1.0)
        x = nextfloat(x)
    end
    return x
end

ans = notequal(1.5)
println("x such that x * (1/x) != 1: ", ans)
println("Value: ", Float64(ans * Float64(1/ans)))
println("Binary representation: ", bitstring(ans))

ans = notequal(1.0)
println("\nSmallest x such that x * (1/x) != 1: ", ans)
println("Value: ", Float64(ans * Float64(1/ans)))
println("Binary representation: ", bitstring(ans))


