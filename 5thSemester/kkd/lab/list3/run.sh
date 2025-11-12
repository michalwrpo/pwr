for i in $(seq 1 3);
do
    for j in $(seq 0 3);
    do
        echo -e "\ntest${i}.bin algorithm: ${j}"
        ./a.out ../list2/test/test${i}.bin coded${i}_${j}.out ${j}
        ./a.out coded${i}_${j}.out decoded${i}_${j}.out ${j} -d
    done
done 