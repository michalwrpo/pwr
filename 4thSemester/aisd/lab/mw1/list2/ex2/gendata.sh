rm -f *.txt


for ((i = 10; i < 60; i += 10)); do
    echo "$i $(../ex1/rand.out $i | ../ex1/insort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> insort1.txt
    echo "$i $(../ex1/rand.out $i | ../ex1/quicksort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> quick_s_1.txt
    echo "$i $(../ex1/rand.out $i | ../ex1/hybridsort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> hybrid_s_1.txt
done

for ((i = 10; i < 60; i += 10)); do
    for ((k = 0; k < 10; k++)); do
        echo "$i $(../ex1/rand.out $i | ../ex1/insort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> insort10.txt
        echo "$i $(../ex1/rand.out $i | ../ex1/quicksort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> quick_s_10.txt
        echo "$i $(../ex1/rand.out $i | ../ex1/hybridsort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> hybrid_s_10.txt
    done
done

for ((i = 10; i < 60; i += 10)); do
    for ((k = 0; k < 100; k++)); do
        echo "$i $(../ex1/rand.out $i | ../ex1/insort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> insort100.txt
        echo "$i $(../ex1/rand.out $i | ../ex1/quicksort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> quick_s_100.txt
        echo "$i $(../ex1/rand.out $i | ../ex1/hybridsort.out | grep Comparisons | cut -d ' ' -f 2,4)" >> hybrid_s_100.txt
    done
done

for ((i = 1000; i <= 50000; i += 1000)); do
    echo "$i $(../ex1/rand.out $i | ../ex1/quicksort.out | cut -d ' ' -f 2,4)" >> quick_l_1.txt
    echo "$i $(../ex1/rand.out $i | ../ex1/hybridsort.out | cut -d ' ' -f 2,4)" >> hybrid_l_1.txt
done

for ((i = 1000; i <= 50000; i += 1000)); do
    for ((k = 0; k < 10; k++)); do
        echo "$i $(../ex1/rand.out $i | ../ex1/quicksort.out | cut -d ' ' -f 2,4)" >> quick_l_10.txt
        echo "$i $(../ex1/rand.out $i | ../ex1/hybridsort.out | cut -d ' ' -f 2,4)" >> hybrid_l_10.txt
    done
done

for ((i = 1000; i <= 50000; i += 1000)); do
    for ((k = 0; k < 100; k++)); do
        echo "$i $(../ex1/rand.out $i | ../ex1/quicksort.out | cut -d ' ' -f 2,4)" >> quick_l_100.txt
        echo "$i $(../ex1/rand.out $i | ../ex1/hybridsort.out | cut -d ' ' -f 2,4)" >> hybrid_l_100.txt
    done
done