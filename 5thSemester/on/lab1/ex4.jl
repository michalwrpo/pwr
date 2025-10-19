# Michał Waluś 279695

function nextFloat(num::Float64)
    x = Float64(1.0)
    while Float64(num) + x != Float64(num)
        x /= Float64(2.0)
    end
    return num + x * Float64(2.0)
end

function notequal(start::Float64)
    x = Float64(start)
    eps = nextFloat(Float64(start)) - Float64(start)
    while Float64(x * Float64(1/x)) == Float64(1.0)
        x += eps
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


