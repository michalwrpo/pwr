# Michał Waluś 279695

function eta16()
    eta = Float16(1.0)
    while eta / Float16(2.0) != Float16(0.0)
        eta /= Float16(2.0)
    end
    return eta
end

function eta32()
    eta = Float32(1.0)
    while eta / Float32(2.0) != Float32(0.0)
        eta /= Float32(2.0)
    end
    return eta
end

function eta64()
    eta = Float64(1.0)
    while eta / Float64(2.0) != Float64(0.0)
        eta /= Float64(2.0)
    end
    return eta
end

println("Float16")
println("Calculated eta: ", eta16())
println("Eta: ", nextfloat(Float16(0.0)))

println("\nFloat32")
println("Calculated eta: ", eta32())
println("Eta: ", nextfloat(Float32(0.0)))

println("\nFloat64")
println("Calculated eta: ", eta64())
println("Eta: ", nextfloat(Float64(0.0)))