rm -rf output/results_?.txt output/results_10.txt output/results_11.txt

for k in {1..11}; do
    for i in {1..100}; do
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1
    done
done 