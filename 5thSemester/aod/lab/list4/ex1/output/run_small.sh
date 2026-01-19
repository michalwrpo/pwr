rm -rf output/results_?.txt

for k in {1..11}; do
    for i in {1..100}; do
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1
    done
done 