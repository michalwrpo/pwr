# Michał Waluś 279695

include("rysuj.jl")

function f(x)
    return exp(x)
end

function g(x)
    return x^2 * sin(x)
end

ns = [5, 10, 15]

for n in ns
    rysujNnfx(f, 0.0, 1.0, n; tytul="Wykres interpolacji funkcji exp(x) dla n=$n", nazwa_pliku="exp_n_$n.png")
    rysujNnfx(g, -1.0, 1.0, n; tytul="Wykres interpolacji funkcji x^2*sin(x) dla n=$n", nazwa_pliku="x2_sin_n_$n.png")
end