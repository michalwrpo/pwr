# Michał Waluś 279695

function next_p(p, r)
    return p + r*p*(1 - p)
end

function iter40(p0, r)
    p = p0
    for _ in 1:40
        p = next_p(p, r)
    end
    return p
end


p0 = 0.01
r = 3.0

println("Using Float32: ", iter40(Float32(p0), Float32(r)))

println("Using Float64: ", iter40(p0, r))
