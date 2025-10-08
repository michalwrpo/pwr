# Michał Waluś 279695

function eps16()
    x = Float16(1.0)
    while Float16(1.0) + x != Float16(1.0)
        x /= Float16(2.0)
    end
    return x * Float16(2.0)
end

function eps32()
    x = Float32(1.0)
    while Float32(1.0) + x != Float32(1.0)
        x /= Float32(2.0)
    end
    return x * Float32(2.0)
end

function eps64()
    x = Float64(1.0)
    while Float64(1.0) + x != Float64(1.0)
        x /= Float64(2.0)
    end
    return x * Float64(2.0)
end

println("Float16")
println("Calculated macheps: ", eps16())
println("1 + cal. macheps: ", Float16(1 + eps16()))
println("Macheps: ", eps(Float16))

println("\nFloat32")
println("Calculated macheps: ", eps32())
println("1 + cal. macheps: ", Float32(1 + eps32()))
println("Macheps: ", eps(Float32))

println("\nFloat64")
println("Calculated macheps: ", eps64())
println("1 + cal. macheps: ", Float64(1 + eps64()))
println("Macheps: ", eps(Float64))
