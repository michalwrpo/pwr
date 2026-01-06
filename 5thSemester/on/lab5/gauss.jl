# Michał Waluś 279695

include("structure.jl")

function elimination_simple(A::A_Matrix{Float64}, b::Vector{Float64})
    n = A.n
    l = A.l
    v = div(n, l)

    # Forward elimination
    for k in 1:v # block
        for i in 1:l # row
            cur = A.An[k][i, i]
            if abs(cur) < 1e-20
                error("Zero encountered at block $k, row $i")
            end
            for j in (i+1):l
                factor = A.An[k][j, i] / cur
                A.An[k][j, i:l] .-= factor * A.An[k][i, i:l]
                b[(k-1)*l + j] -= factor * b[(k-1)*l + i]

                # Update Cn
                if k < v # no Cn to the right of it
                    A.Cn[k][j, 1:i] .-= factor * A.Cn[k][i, 1:i] # i-th row of Cn has 0 on positions > i
                end
            end
            if k == v
                continue # No Bn below last An block 
            end
            # Update Bn
            factor = A.Bn[k][i] / cur
            A.Bn[k][i:l] .-= factor * A.An[k][i, i:l]
            A.An[k+1][1, 1:l] .-= factor * A.Cn[k][i, 1:l] # C_k is directly above A_(k+1)
            b[k * l + 1] -= factor * b[(k-1)*l + i]

            if i == l
                for j in 2:l
                    factor = A.Bn[k][l-1 + j] / cur
                    A.Bn[k][l-1 + j] = 0.0
                    A.An[k+1][j, 1:l] .-= factor * A.Cn[k][l, 1:l] # C_k is directly above A_(k+1)

                    b[k*l + j] -= factor * b[k*l]
                end
            end
        end
    end

    x = Vector{Float64}(undef, n)

    for k in n:-1:1
        sum = b[k]
        block = div(k - 1, l) + 1
        local_k = mod(k - 1, l) + 1

        for j in (local_k + 1):l
            sum -= A.An[block][local_k, j] * x[(block - 1)*l + j]
        end
        if block < v
            for j in 1:local_k
                sum -= A.Cn[block][local_k, j] * x[(block)*l + j]
            end
        end
        x[k] = sum / A.An[block][local_k, local_k]
    end

    println("Solution vector x:")
    println(x)

    return x
end

function elimination_choice(A::A_Matrix{Float64}, b::Vector{Float64})
    n = A.n
    l = A.l
    v = div(n, l)

    Dn = [zeros(Float64, 2*l - 1) for _ in 1:(v-2)] # to store moved Cn rows, has mirrored structure of Bn

    # Forward elimination
    for k in 1:v
        # Process block A_k
        for i in 1:l
            chosen = i;
            cur = A.An[k][i, i]
            for j in (i+1):l
                if abs(A.An[k][j, i]) > abs(cur)
                    cur = A.An[k][j, i]
                    chosen = j
                end
            end
            if k < v
                if abs(A.Bn[k][i]) > abs(cur)
                    cur = A.Bn[k][i]
                    chosen = l + 1
                end
                if i == l 
                    for j in 2:l
                        if abs(A.Bn[k][l-1 + j]) > abs(cur)
                            cur = A.Bn[k][l-1 + j]
                            chosen = l + j
                        end
                    end
                end
            end

            if chosen > i && chosen <= l # if it's i then we don't need to switch
                for col in i:l
                    A.An[k][i, col], A.An[k][chosen, col] = A.An[k][chosen, col], A.An[k][i, col]
                end

                b[(k-1)*l + i], b[(k-1)*l + chosen] = b[(k-1)*l + chosen], b[(k-1)*l + i]

                if k < v
                    for col in 1:l
                        A.Cn[k][i, col], A.Cn[k][chosen, col] = A.Cn[k][chosen, col], A.Cn[k][i, col]
                    end
                    if k < v - 1
                        Dn[k][i], Dn[k][chosen] = Dn[k][chosen], Dn[k][i]
                    end
                end                    
            elseif chosen == l + 1
                # switch with Bn
                for col in i:l
                    A.An[k][i, col], A.Bn[k][col] = A.Bn[k][col], A.An[k][i, col]
                end

                b[(k-1)*l + i], b[k * l + 1] = b[k * l + 1], b[(k-1)*l + i]

                for col in 1:l
                    A.Cn[k][i, col], A.An[k+1][1, col] = A.An[k+1][1, col], A.Cn[k][i, col]
                end

                if k < v - 1
                    Dn[k][i], A.Cn[k+1][1, 1] = A.Cn[k+1][1, 1], Dn[k][i]
                end
            elseif chosen > l + 1
                # i has to be l here
                row = chosen - l

                A.An[k][l, l], A.Bn[k][l-1 + row] = A.Bn[k][l-1 + row], A.An[k][l, l]

                b[k*l], b[k * l + row] = b[k * l + row], b[k*l]

                for col in 1:l
                    A.Cn[k][l, col], A.An[k+1][row, col] = A.An[k+1][row, col], A.Cn[k][l, col]
                end

                if k < v - 1
                    for col in 1:l
                        Dn[k][l-1 + col], A.Cn[k+1][row, col] = A.Cn[k+1][row, col], Dn[k][l-1 + col]
                    end
                end
            end
            
            # Now perform elimination as usual
            cur = A.An[k][i, i]

            if abs(cur) < 1e-50
                error("Zero encountered at block $k, row $i")
            end

            for j in (i+1):l
                factor = A.An[k][j, i] / cur
                A.An[k][j, i:l] .-= factor * A.An[k][i, i:l]
                b[(k-1)*l + j] -= factor * b[(k-1)*l + i]

                # Update Cn
                if k < v # no Cn to the right of it
                    A.Cn[k][j, 1:l] .-= factor * A.Cn[k][i, 1:l] 
                end
                # Update Dn
                if k < v - 1
                    Dn[k][j] -= factor * Dn[k][i]
                end
            end
            if k == v
                continue # No Bn below last An block 
            end
            # Update Bn
            factor = A.Bn[k][i] / cur
            A.Bn[k][i:l] .-= factor * A.An[k][i, i:l]
            A.An[k+1][1, 1:l] .-= factor * A.Cn[k][i, 1:l] # C_k is directly above A_(k+1)

            b[k * l + 1] -= factor * b[(k-1)*l + i]
            
            if k < v - 1
                A.Cn[k+1][1, 1] -= factor * Dn[k][i] # D_k is directly above C_(k+1)
            end

            if i == l
                if k < v - 1
                    A.Cn[k+1][1, 2:l] .-= factor * Dn[k][l+1:2*l-1] # rest of Dn row to C_(k+1)
                end

                for j in 2:l
                    factor = A.Bn[k][l-1 + j] / cur
                    A.Bn[k][l-1 + j] = 0.0
                    A.An[k+1][j, 1:l] .-= factor * A.Cn[k][l, 1:l] # C_k is directly above A_(k+1)
                    
                    b[k*l + j] -= factor * b[k*l]

                    if k < v - 1
                        A.Cn[k+1][j, 1:l] .-= factor * Dn[k][l:2*l-1] # D_k is directly above C_(k+1)
                    end
                end
            end
        end
    end

    x = Vector{Float64}(undef, n)

    for k in n:-1:1
        sum = b[k]
        block = div(k - 1, l) + 1
        local_k = mod(k - 1, l) + 1

        for j in (local_k + 1):l
            sum -= A.An[block][local_k, j] * x[(block - 1)*l + j]
        end
        if block < v
            for j in 1:l
                sum -= A.Cn[block][local_k, j] * x[(block)*l + j]
            end
            if block < v - 1
                sum -= Dn[block][local_k] * x[(block + 1)*l + 1]
                if local_k == l
                    for j in 2:l
                        sum -= Dn[block][l-1 + j] * x[(block + 1)*l + j]
                    end
                end
            end
        end
        x[k] = sum / A.An[block][local_k, local_k]
    end

    println("Solution vector x:")
    println(x)

    return x
end

function LU_simple(A::A_Matrix{Float64})
    n = A.n
    l = A.l
    v = div(n, l)

    # Forward elimination
    for k in 1:v # block
        for i in 1:l # row
            cur = A.An[k][i, i]
            if abs(cur) < 1e-20
                error("Zero encountered at block $k, row $i")
            end
            for j in (i+1):l
                factor = A.An[k][j, i] / cur
                A.An[k][j, i:l] .-= factor * A.An[k][i, i:l]
                A.An[k][j, i] = factor # store L factor

                # Update Cn
                if k < v # no Cn to the right of it
                    A.Cn[k][j, 1:i] .-= factor * A.Cn[k][i, 1:i] # i-th row of Cn has 0 on positions > i
                end
            end
            if k == v
                continue # No Bn below last An block 
            end
            # Update Bn
            factor = A.Bn[k][i] / cur
            A.Bn[k][i:l] .-= factor * A.An[k][i, i:l]
            A.Bn[k][i] = factor # store L factor
            A.An[k+1][1, 1:l] .-= factor * A.Cn[k][i, 1:l] # C_k is directly above A_(k+1)

            if i == l
                for j in 2:l
                    factor = A.Bn[k][l-1 + j] / cur
                    A.Bn[k][l-1 + j] = factor # store L factor
                    A.An[k+1][j, 1:l] .-= factor * A.Cn[k][l, 1:l] # C_k is directly above A_(k+1)
                end
            end
        end
    end
end

function solve_LU_simple(A::A_Matrix{Float64}, b::Vector{Float64})
    n = A.n
    l = A.l
    v = div(n, l)

    # Forward substitution Ly = b
    for k in 1:v # block
        for i in 1:l # row
            for j in (i+1):l
                b[(k-1)*l + j] -= A.An[k][j, i] * b[(k-1)*l + i]
            end
            if k == v
                continue # No Bn below last An block 
            end
            b[k * l + 1] -= A.Bn[k][i] * b[(k-1)*l + i]

            if i == l
                for j in 2:l
                    b[k*l + j] -= A.Bn[k][l-1 + j] * b[k*l]
                end
            end
        end
    end

    # Backward substitution Ux = y
    x = Vector{Float64}(undef, n)
    for k in n:-1:1
        sum = b[k]
        block = div(k - 1, l) + 1
        local_k = mod(k - 1, l) + 1

        for j in (local_k + 1):l
            sum -= A.An[block][local_k, j] * x[(block - 1)*l + j]
        end
        if block < v
            for j in 1:l
                sum -= A.Cn[block][local_k, j] * x[(block)*l + j]
            end
        end
        x[k] = sum / A.An[block][local_k, local_k]
    end

    println("Solution vector x:")
    println(x)

    return x
end

function LU_choice(A::A_Matrix{Float64})
    n = A.n
    l = A.l
    v = div(n, l)

    Dn = [zeros(Float64, 2*l - 1) for _ in 1:(v-2)] # to store moved Cn rows, has mirrored structure of Bn

    # Forward elimination
    for k in 1:v
        # Process block A_k
        for i in 1:l
            chosen = i;
            cur = A.An[k][i, i]
            for j in (i+1):l
                if abs(A.An[k][j, i]) > abs(cur)
                    cur = A.An[k][j, i]
                    chosen = j
                end
            end
            if k < v
                if abs(A.Bn[k][i]) > abs(cur)
                    cur = A.Bn[k][i]
                    chosen = l + 1
                end
                if i == l 
                    for j in 2:l
                        if abs(A.Bn[k][l-1 + j]) > abs(cur)
                            cur = A.Bn[k][l-1 + j]
                            chosen = l + j
                        end
                    end
                end
            end

            if chosen > i && chosen <= l # if it's i then we don't need to switch
                for col in i:l
                    A.An[k][i, col], A.An[k][chosen, col] = A.An[k][chosen, col], A.An[k][i, col]
                end

                if k < v
                    for col in 1:l
                        A.Cn[k][i, col], A.Cn[k][chosen, col] = A.Cn[k][chosen, col], A.Cn[k][i, col]
                    end
                    if k < v - 1
                        Dn[k][i], Dn[k][chosen] = Dn[k][chosen], Dn[k][i]
                    end
                end                    
            elseif chosen == l + 1
                # switch with Bn
                for col in i:l
                    A.An[k][i, col], A.Bn[k][col] = A.Bn[k][col], A.An[k][i, col]
                end

                for col in 1:l
                    A.Cn[k][i, col], A.An[k+1][1, col] = A.An[k+1][1, col], A.Cn[k][i, col]
                end

                if k < v - 1
                    Dn[k][i], A.Cn[k+1][1, 1] = A.Cn[k+1][1, 1], Dn[k][i]
                end
            elseif chosen > l + 1
                # i has to be l here
                row = chosen - l

                A.An[k][l, l], A.Bn[k][l-1 + row] = A.Bn[k][l-1 + row], A.An[k][l, l]

                for col in 1:l
                    A.Cn[k][l, col], A.An[k+1][row, col] = A.An[k+1][row, col], A.Cn[k][l, col]
                end

                if k < v - 1
                    for col in 1:l
                        Dn[k][l-1 + col], A.Cn[k+1][row, col] = A.Cn[k+1][row, col], Dn[k][l-1 + col]
                    end
                end
            end
            
            # Now perform elimination as usual
            cur = A.An[k][i, i]

            if abs(cur) < 1e-50
                error("Zero encountered at block $k, row $i")
            end

            for j in (i+1):l
                factor = A.An[k][j, i] / cur
                A.An[k][j, i:l] .-= factor * A.An[k][i, i:l]
                A.An[k][j, i] = factor # store L factor

                # Update Cn
                if k < v # no Cn to the right of it
                    A.Cn[k][j, 1:l] .-= factor * A.Cn[k][i, 1:l] 
                end
                # Update Dn
                if k < v - 1
                    Dn[k][j] -= factor * Dn[k][i]
                end
            end
            if k == v
                continue # No Bn below last An block 
            end
            # Update Bn
            factor = A.Bn[k][i] / cur
            A.Bn[k][i:l] .-= factor * A.An[k][i, i:l]
            A.Bn[k][i] = factor # store L factor
            A.An[k+1][1, 1:l] .-= factor * A.Cn[k][i, 1:l] # C_k is directly above A_(k+1)
            
            if k < v - 1
                A.Cn[k+1][1, 1] -= factor * Dn[k][i] # D_k is directly above C_(k+1)
            end

            if i == l
                if k < v - 1
                    A.Cn[k+1][1, 2:l] .-= factor * Dn[k][l+1:2*l-1] # rest of Dn row to C_(k+1)
                end

                for j in 2:l
                    factor = A.Bn[k][l-1 + j] / cur
                    A.Bn[k][l-1 + j] = factor
                    A.An[k+1][j, 1:l] .-= factor * A.Cn[k][l, 1:l] # C_k is directly above A_(k+1)

                    if k < v - 1
                        A.Cn[k+1][j, 1:l] .-= factor * Dn[k][l:2*l-1] # D_k is directly above C_(k+1)
                    end
                end
            end
        end
    end
    return Dn
end


function solve_LU_choice(A::A_Matrix{Float64}, Dn::Vector{Vector{Float64}}, b::Vector{Float64})
    n = A.n
    l = A.l
    v = div(n, l)

    for k in 1:v
        for i in 1:l
            for j in (i+1):l
                b[(k-1)*l + j] -= A.An[k][j, i] * b[(k-1)*l + i]
            end
            if k == v
                continue # No Bn below last An block 
            end

            b[k * l + 1] -= A.Bn[k][i] * b[(k-1)*l + i]
            
            if i == l
                for j in 2:l                    
                    b[k*l + j] -= A.Bn[k][l-1 + j] * b[k*l]
                end
            end
        end
    end

    x = Vector{Float64}(undef, n)

    for k in n:-1:1
        sum = b[k]
        block = div(k - 1, l) + 1
        local_k = mod(k - 1, l) + 1

        for j in (local_k + 1):l
            sum -= A.An[block][local_k, j] * x[(block - 1)*l + j]
        end
        if block < v
            for j in 1:l
                sum -= A.Cn[block][local_k, j] * x[(block)*l + j]
            end
            if block < v - 1
                sum -= Dn[block][local_k] * x[(block + 1)*l + 1]
                if local_k == l
                    for j in 2:l
                        sum -= Dn[block][l-1 + j] * x[(block + 1)*l + j]
                    end
                end
            end
        end
        x[k] = sum / A.An[block][local_k, local_k]
    end

    println("Solution vector x:")
    println(x)

    return x
end