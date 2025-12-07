# Michał Waluś 279695

include("rysuj.jl")

function f(x)
    return abs(x)
end

function g(x)
    return 1/(1 + x^2)
end

ns = [5, 10, 15]

for n in ns
    rysujNnfx(f, -1.0, 1.0, n; tytul="|x| dla n=$n (rownoodlegle)", nazwa_pliku="abs_n_$n.png")
    rysujNnfx(g, -5.0, 5.0, n; tytul="1/(1 + x ^2) dla n=$n (rownoodlegle)", nazwa_pliku="frac_n_$n.png")
    rysujNnfx(f, -1.0, 1.0, n; wezly=:czebyszew, tytul="|x| dla n=$n (czebyszew)", nazwa_pliku="cabs_n_$n.png")
    rysujNnfx(g, -5.0, 5.0, n; wezly=:czebyszew, tytul="1/(1 + x ^2) dla n=$n (czebyszew)", nazwa_pliku="cfrac_n_$n.png")
end