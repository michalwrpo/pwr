for n in {1000..10000..1000};
do
    for i in {1..10};
    do
        ./prim.out $n
        ./kruskal.out $n
    done
done