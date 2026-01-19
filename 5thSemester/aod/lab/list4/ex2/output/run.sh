rm -rf output/*.txt

for k in {3..10}; do
    for i in $(seq 1 $k); do
        echo "Size $k, degree $i"
        for j in {1..100}; do
            ./matching.out --size $k --degree $i >> output/results_${k}_${i}.txt 2>&1
        done
    done
done 