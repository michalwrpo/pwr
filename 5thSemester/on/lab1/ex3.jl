# Michał Waluś 279695

function floatCount(start::Float64=1.0, intervalEnd::Float64=2.0)
    count = 2
    x = nextfloat(start)
    while 2 * x - start < intervalEnd
        x = 2 * x - start
        count *= 2
    end
    return count
end

println("Number of Float64 numbers in [1.0, 2.0): ", floatCount(1.0, 2.0))
println("Representation of nextfloat(1.0): ", bitstring(nextfloat(Float64(1.0))))

println("\nNumber of Float64 numbers in [0.5, 1.0): ", floatCount(0.5, 1.0))
println("Representation of nextfloat(0.5): ", bitstring(nextfloat(Float64(0.5))))

println("\nNumber of Float64 numbers in [2.0, 4.0): ", floatCount(2.0, 4.0))
println("Representation of nextfloat(2.0): ", bitstring(nextfloat(Float64(2.0))))
