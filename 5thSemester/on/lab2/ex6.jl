# Michał Waluś 279695

function next_x(x, c)
    return x^2 + c
end

function iter40(x0, c)
    x = x0
    for i in 1:40
        x = next_x(x, c)
        # println(i, " ", x)
    end
    return x
end

cs = [-2, -2, -2, -1, -1, -1, -1]
xs = [1, 2, 1.99999999999999, 1, -1, 0.75, 0.25]

for i in 1:7
    println("c=", cs[i], " x0=", xs[i], " x40=", iter40(xs[i], cs[i]))
end
