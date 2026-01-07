# Michał Waluś 279695

module myplot

export plot1, plot2, plot3

include("blocksys.jl")
using .blocksys
using Plots

function plot1()
    base = "examples/"

    dirs = ["16", "10_000", "50_000", "100_000", "500_000", "750_000", "1_000_000"]

    time = [Vector{Float64}(undef, 7) for _ in 1:4]

    for i in 1:7
        path = base * dirs[i]
        time[1][i] = solve_Gauss(path * "/A.txt", path * "/b.txt", "foo.txt")
        time[2][i] = solve_Gauss_choice(path * "/A.txt", path * "/b.txt", "foo.txt")
        time[3][i] = solve_LU(path * "/A.txt", path * "/b.txt", "foo.txt")
        time[4][i] = solve_LU_pivot(path * "/A.txt", path * "/b.txt", "foo.txt")
    end

    sizes = [parse(Int, replace(d, "_" => "")) for d in dirs]

    labels = ["Gauss (bez wyboru)" "Gauss (z wyborem)" "LU (bez wyboru)" "LU (z wyborem)"]

    p = plot(
        sizes, 
        [time[1] time[2] time[3] time[4]], 
        label = labels,
        title = "Porównanie czasu wykonania algorytmów (l = 4)",
        xlabel = "Rozmiar macierzy (n)",
        ylabel = "Czas (s)",
        lw = 2,               
        marker = :circle,     
        markersize = 4,
        xscale = :identity,
        yscale = :identity,
        legend = :topleft
    )

    savefig(p, "plot1.png")

    p = plot(
        sizes, 
        [time[1] time[2] time[3] time[4]], 
        label = labels,
        title = "Porównanie czasu wykonania algorytmów (l = 4)",
        xlabel = "Rozmiar macierzy (n)",
        ylabel = "Czas (s)",
        lw = 2,               
        marker = :circle,     
        markersize = 4,
        xscale = :log10,      
        yscale = :log10,      
        legend = :topleft
    )

    savefig(p, "plot1_log.png")

    for i in 1:4
        println(time[i])
    end
end

function plot2()
    base = "examples/l_test/"
    
    # Wartości l odpowiadające plikom w katalogu (l2.txt, l4.txt itd.)
    # Sortujemy je, aby oś X była monotoniczna
    l_values = [4, 6, 8, 10, 12]
    num_points = length(l_values)

    # Przygotowanie tablicy na czasy (4 algorytmy)
    times = [Vector{Float64}(undef, num_points) for _ in 1:4]
    
    # Plik tymczasowy na wyniki (nie jest nam potrzebny do wykresu, ale check_ wymaga ścieżki)
    temp_out = "temp_plot2_out.txt"

    for (i, l) in enumerate(l_values)
        file_name = "l$l.txt"
        path = base * file_name
        
        println("Przetwarzanie: $file_name")
        
        # Funkcje check_ zwracają czas wykonania (według Twojej wcześniejszej modyfikacji)
        # check_ generuje b wewnątrz, więc podajemy tylko plik macierzy A i plik wyjściowy
        times[1][i] = check_Gauss(path, temp_out)
        times[2][i] = check_Gauss_choice(path, temp_out)
        times[3][i] = check_LU(path, temp_out)
        times[4][i] = check_LU_pivot(path, temp_out)
    end

    # Etykiety
    labels = ["Gauss (bez wyboru)" "Gauss (z wyborem)" "LU (bez wyboru)" "LU (z wyborem)"]

    # 1. Wykres w skali liniowej
    p1 = plot(
        l_values, 
        [times[1] times[2] times[3] times[4]], 
        label = labels,
        title = "Zależność czasu od rozmiaru bloku (n = 300000)",
        xlabel = "Rozmiar bloku (l)",
        ylabel = "Czas (s)",
        lw = 2,               
        marker = :circle,     
        markersize = 4,
        xscale = :identity,
        yscale = :identity,
        legend = :topleft 
    )

    savefig(p1, "plot2.png")


    for k in 1:5
        print(l_values[k], " & ")
        for i in 1:4
            print(times[i][k], " & ")
        end
        println("\b\b\\\\")
    end

    rm(temp_out, force=true)
end

function plot3()
    base = "examples/n_test/"
    
    # Pliki to n1.txt ... n10.txt
    k_values = 1:10
    
    # Zgodnie z opisem: n = k * 100 000
    n_values = k_values .* 100_000
    num_points = length(k_values)

    # Przygotowanie tablicy na czasy (4 algorytmy)
    times = [Vector{Float64}(undef, num_points) for _ in 1:4]
    
    temp_out = "temp_plot3_out.txt"

    for (i, k) in enumerate(k_values)
        file_name = "n$k.txt"
        path = base * file_name
        
        println("Przetwarzanie: $file_name (n = $(n_values[i]))")
        
        # Mierzymy czas dla 4 metod
        times[1][i] = check_Gauss(path, temp_out)
        times[2][i] = check_Gauss_choice(path, temp_out)
        times[3][i] = check_LU(path, temp_out)
        times[4][i] = check_LU_pivot(path, temp_out)
    end

    labels = ["Gauss (bez wyboru)" "Gauss (z wyborem)" "LU (bez wyboru)" "LU (z wyborem)"]

    p1 = plot(
        n_values, 
        [times[1] times[2] times[3] times[4]], 
        label = labels,
        title = "Zależność czasu od rozmiaru macierzy (l = 4)",
        xlabel = "Rozmiar macierzy (n)",
        ylabel = "Czas (s)",
        lw = 2,               
        marker = :circle,     
        markersize = 4,
        xscale = :identity,
        yscale = :identity,
        legend = :topleft 
    )

    savefig(p1, "plot3.png")


    for k in 1:num_points
        print(n_values[k], " & ")
        for i in 1:4
            print(times[i][k], " & ")
        end
        println("\b\b\\\\")
    end

    rm(temp_out, force=true)
end

end