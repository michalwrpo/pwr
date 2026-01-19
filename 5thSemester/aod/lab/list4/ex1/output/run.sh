rm -rf output/*.txt

for k in {1..16}; do
    for i in {1..10}; do
        echo "Run #$i with size $k"
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1 &
        ./app.out --size $k >> output/results_$k.txt 2>&1
    done
done 