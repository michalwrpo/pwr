rm -rf output/*.txt

for k in {1..16}; do
    for i in {1..10}; do
        echo "Run #$i with size $k"
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1 &
        ./maxflow.out --size $k >> output/results_$k.txt 2>&1
    done
done 