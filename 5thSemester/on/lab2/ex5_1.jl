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

function iter10_30(p0, r)
    p = p0
    for i in 1:40
        p = next_p(p,r)
        if i == 10
            p = round(p, RoundDown, digits=3)
            println("After 10: ", p)
        end
    end
    return p
end

p0 = Float32(0.01)
r = Float32(3)

println("After 40 iterations: ", iter40(p0, r))

println("After 10 + 30 iterations: ", iter10_30(p0, r))
