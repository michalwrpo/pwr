# Michał Waluś 279695

x = [2.718281828, −3.141592654, 1.414213562, 0.5772156649, 0.3010299957]
x1 = [2.718281828, −3.141592654, 1.414213562, 0.577215664, 0.301029995]
y = [1486.2497, 878366.9879, −22.37492, 4773714.647, 0.000185049]

function forward32(x::Vector{Float32}, y::Vector{Float32}, n::Int=length(x))
    S = Float32(0.0)
    for i in 1:n
        S += Float32(x[i]) * Float32(y[i])
    end
    return S
end

function forward64(x::Vector{Float64}, y::Vector{Float64}, n::Int=length(x))
    S = Float64(0.0)
    for i in 1:n
        S += Float64(x[i]) * Float64(y[i])
    end
    return S    
end

function backward32(x::Vector{Float32}, y::Vector{Float32}, n::Int=length(x))
    S = Float32(0.0)
    for i in n:-1:1
        S += Float32(x[i]) * Float32(y[i])
    end
    return S
end

function backward64(x::Vector{Float64}, y::Vector{Float64}, n::Int=length(x))
    S = Float64(0.0)
    for i in n:-1:1
        S += Float64(x[i]) * Float64(y[i])
    end
    return S 
end

function fromBiggest32(x::Vector{Float32}, y::Vector{Float32})
    S1 = Float32(0.0)
    S2 = Float32(0.0)
    xy = [x * y for (x, y) in zip(x, y)]

    xy1 = filter(x -> x >= 0, xy)
    xy2 = filter(x -> x < 0, xy)
    xy1 = sort(xy1, rev=true)
    xy2 = sort(xy2)

    for num in xy1
        S1 += Float32(num)
    end
    for num in xy2
        S2 += Float32(num)
    end
    return S1 + S2
end

function fromBiggest64(x::Vector{Float64}, y::Vector{Float64})
    S1 = Float64(0.0)
    S2 = Float64(0.0)
    xy = [x * y for (x, y) in zip(x, y)]

    xy1 = filter(x -> x >= 0, xy)
    xy2 = filter(x -> x < 0, xy)
    xy1 = sort(xy1, rev=true)
    xy2 = sort(xy2)

    for num in xy1
        S1 += Float64(num)
    end
    for num in xy2
        S2 += Float64(num)
    end
    return S1 + S2
end

function fromSmallest32(x::Vector{Float32}, y::Vector{Float32})
    S1 = Float32(0.0)
    S2 = Float32(0.0)
    xy = [x * y for (x, y) in zip(x, y)]

    xy1 = filter(x -> x >= 0, xy)
    xy2 = filter(x -> x < 0, xy)
    xy1 = sort(xy1)
    xy2 = sort(xy2, rev=true)

    for num in xy1
        S1 += Float32(num)
    end
    for num in xy2
        S2 += Float32(num)
    end
    return S1 + S2
end

function fromSmallest64(x::Vector{Float64}, y::Vector{Float64})
    S1 = Float64(0.0)
    S2 = Float64(0.0)
    xy = [x * y for (x, y) in zip(x, y)]

    xy1 = filter(x -> x >= 0, xy)
    xy2 = filter(x -> x < 0, xy)
    xy1 = sort(xy1)
    xy2 = sort(xy2, rev=true)

    for num in xy1
        S1 += Float64(num)
    end
    for num in xy2
        S2 += Float64(num)
    end

    return S1 + S2
end

println("Float32 forward: ", forward32(Float32.(x), Float32.(y), 5))
println("Float32 backward: ", backward32(Float32.(x), Float32.(y), 5))
println("Float32 from biggest: ", fromBiggest32(Float32.(x), Float32.(y)))
println("Float32 from smallest: ", fromSmallest32(Float32.(x), Float32.(y)))

println("\nFloat64 forward: ", forward64(Float64.(x), Float64.(y), 5))
println("Float64 backward: ", backward64(Float64.(x), Float64.(y), 5))
println("Float64 from biggest: ", fromBiggest64(Float64.(x), Float64.(y)))
println("Float64 from smallest: ", fromSmallest64(Float64.(x), Float64.(y)))

println("\nResults for x1:\n")

println("Float32 forward: ", forward32(Float32.(x1), Float32.(y), 5))
println("Float32 backward: ", backward32(Float32.(x1), Float32.(y), 5))
println("Float32 from biggest: ", fromBiggest32(Float32.(x1), Float32.(y)))
println("Float32 from smallest: ", fromSmallest32(Float32.(x1), Float32.(y)))

println("\nFloat64 forward: ", forward64(Float64.(x1), Float64.(y), 5))
println("Float64 backward: ", backward64(Float64.(x1), Float64.(y), 5))
println("Float64 from biggest: ", fromBiggest64(Float64.(x1), Float64.(y)))
println("Float64 from smallest: ", fromSmallest64(Float64.(x1), Float64.(y)))