# Michał Waluś 279695

function kahan16()
    return Float16(3.0) * (Float16(4.0) / Float16(3.0) - Float16(1.0)) - Float16(1.0)
end

function kahan32()
    return Float32(3.0) * (Float32(4.0) / Float32(3.0) - Float32(1.0)) - Float32(1.0)
end

function kahan64()
    return Float64(3.0) * (Float64(4.0) / Float64(3.0) - Float64(1.0)) - Float64(1.0)
end

println("Float16")
println("Kahan's method: ", kahan16())
println("Macheps: ", eps(Float16))

println("\nFloat32")
println("Kahan's method: ", kahan32())
println("Macheps: ", eps(Float32))

println("\nFloat64")
println("Kahan's method: ", kahan64())
println("Macheps: ", eps(Float64))