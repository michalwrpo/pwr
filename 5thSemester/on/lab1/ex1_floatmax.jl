# Michał Waluś 279695

function max16()
    x = Float16(1.0)
    while Float16(1.0) - x / Float16(2.0) != Float16(1.0)
        x /= Float16(2.0)
    end
    x = Float16(1.0) - x
    while !isinf(x * 2)
        x = (x * 2)
    end
    return x
end

function max32()
    x = Float32(1.0)
    while Float32(1.0) - x / Float32(2.0) != Float32(1.0)
        x /= Float32(2.0)
    end
    x = Float32(1.0) - x
    while !isinf(x * 2)
        x = (x * 2)
    end
    return x
end

function max64()
    x = Float64(1.0)
    while Float64(1.0) - x / Float64(2.0) != Float64(1.0)
        x /= Float64(2.0)
    end
    x = Float64(1.0) - x
    while !isinf(x * 2)
        x = (x * 2)
    end
    return x
end

println("Calculated Float16 max: ", max16())
println("Float16 max: ", floatmax(Float16))

println("\nCalculated Float32 max: ", max32())
println("Float32 max: ", floatmax(Float32))

println("\nCalculated Float64 max: ", max64())
println("Float64 max: ", floatmax(Float64))