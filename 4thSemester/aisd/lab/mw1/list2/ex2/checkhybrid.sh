rm hybrid.txt

for ((k = 1; k < 11; k++)) do
    for ((i = 0; i < 100; i++)); do
        (echo -n "$k " && ../ex1/rand.out 10000 | ../ex1/hybridsort.out $k | cut -d " " -f 2,4) >> hybrid.txt
    done
done