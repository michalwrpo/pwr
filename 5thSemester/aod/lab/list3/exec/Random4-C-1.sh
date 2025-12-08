for i in {0..15}; do
    ./app.out dijkstra -d inputs/Random4-C/Random4-C.$i.0.gr -ss inputs/Random4-C/Random4-C-1.ss -oss outputs/Random4-C/Random4-C-d.$i.1.ss.res
    # ./app.out dial -d inputs/Random4-C/Random4-C.$i.0.gr -ss inputs/Random4-C/Random4-C-1.ss -oss outputs/Random4-C/Random4-C-l.$i.1.ss.res
    ./app.out radixheap -d inputs/Random4-C/Random4-C.$i.0.gr -ss inputs/Random4-C/Random4-C-1.ss -oss outputs/Random4-C/Random4-C-r.$i.1.ss.res
done