# Michał Waluś 279695

include("ilorazy.jl")
include("val_newton.jl")

using Plots

function rysujNnfx(f,a::Float64,b::Float64,n::Int; wezly::Symbol = :rownoodlegle, tytul::String = "", nazwa_pliku::String = "")
    x = zeros(Float64, n+1)
    fx = zeros(Float64, n+1)

    if wezly == :rownoodlegle
        for i in 1:n+1
            x[i] = a + (i - 1) * (b - a) / n
            fx[i] = f(x[i])
        end
    elseif wezly == :czebyszew
        for i in 1:n+1
            x[i] = (a+b)/2 + (b - a)/2 * cos((2 * i - 1) * π / (2 * (n + 1)))
            fx[i] = f(x[i])
        end
    else
        error("Nieznany typ węzłów: $wezly")
    end

    coeffs = ilorazyRoznicowe(x, fx)

    xs = collect(a:(b-a)/10000:b)
    ys = [warNewton(x, coeffs, xi) for xi in xs]
    ys2 = [f(xi) for xi in xs]


    p = plot(xs, ys, label="Wielomian interpolacyjny w formie Newtona", legend=:outerbottom)
    plot!(p, xs, ys2, label="Funkcja oryginalna", linestyle=:dash)
    scatter!(p, x, fx, label="Węzły interpolacji", color=:red)
    xlabel!(p, "x")
    ylabel!(p, "P(x)")
    
    if tytul != ""
        title!(tytul)
    else
        title!(p, "Interpolacja w formie Newtona, węzły $(wezly), n=$n", titlefontsize=8) 
    end

    

    if nazwa_pliku == ""
        nazwa_pliku = "$(n)_$(wezly).png"
    end
    savefig(p, nazwa_pliku)
    gui()
end

