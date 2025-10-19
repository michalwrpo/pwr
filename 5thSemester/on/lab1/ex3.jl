# Michał Waluś 279695

function nextFloat(num::Float64)
    x = Float64(1.0)
    while Float64(num) + x != Float64(num)
        x /= Float64(2.0)
    end
    return num + x * Float64(2.0)
end

function floatCount(start::Float64=1.0, intervalEnd::Float64=2.0)
    count = 2
    x = nextFloat(start)
    while 2 * x - start < intervalEnd
        x = 2 * x - start
        count *= 2
    end
    return count
end

function prevFloat(num::Float64)
    x = Float64(1.0)
    while Float64(num) - x != Float64(num)
        x /= Float64(2.0)
    end
    return num - x * Float64(2.0)
end

println("Number of Float64 numbers in [1.0, 2.0): ", floatCount(1.0, 2.0), ", log2: ", log2(floatCount(1.0, 2.0)))
println("Representation of 1.0:            ", bitstring(Float64(1.0)))
println("Representation of nextFloat(1.0): ", bitstring(nextFloat(Float64(1.0))))
println("Step: ", log2(nextFloat(Float64(1.0)) - Float64(1.0)))
println("Representation of prevFloat(2.0): ", bitstring(prevFloat(Float64(2.0))))
println("Representation of 2.0:            ", bitstring(Float64(2.0)))
println("Step: ", log2(Float64(2.0) - prevFloat(Float64(2.0))))

println("\nNumber of Float64 numbers in [0.5, 1.0): ", floatCount(0.5, 1.0), ", log2: ", log2(floatCount(0.5, 1.0)))
println("Representation of 0.5:            ", bitstring(Float64(0.5)))
println("Representation of nextFloat(0.5): ", bitstring(nextFloat(Float64(0.5))))
println("Step: ", log2(nextFloat(Float64(0.5)) - Float64(0.5)))
println("Representation of prevFloat(1.0): ", bitstring(prevFloat(Float64(1.0))))
println("Representation of 1.0:            ", bitstring(Float64(1.0)))
println("Step: ", log2(Float64(1.0) - prevFloat(Float64(1.0))))

println("\nNumber of Float64 numbers in [2.0, 4.0): ", floatCount(2.0, 4.0), ", log2: ", log2(floatCount(2.0, 4.0)))
println("Representation of 2.0:            ", bitstring(Float64(2.0)))
println("Representation of nextFloat(2.0): ", bitstring(nextFloat(Float64(2.0))))
println("Step: ", log2(nextFloat(Float64(2.0)) - Float64(2.0)))
println("Representation of prevFloat(4.0): ", bitstring(prevFloat(Float64(4.0))))
println("Representation of 4.0:            ", bitstring(Float64(4.0)))
println("Step: ", log2(Float64(4.0) - prevFloat(Float64(4.0))))