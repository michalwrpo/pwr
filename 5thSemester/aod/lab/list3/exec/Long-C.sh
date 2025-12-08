for i in {0..15}; do
    # ./app.out dijkstra -d inputs/Long-C/Long-C.$i.0.gr -ss inputs/Long-C/Long-C.ss -oss outputs/Long-C/Long-C-d.$i.0.ss.res
    ./app.out dial -d inputs/Long-C/Long-C.$i.0.gr -ss inputs/Long-C/Long-C.ss -oss outputs/Long-C/Long-C-l.$i.0.ss.res
    # ./app.out radixheap -d inputs/Long-C/Long-C.$i.0.gr -ss inputs/Long-C/Long-C.ss -oss outputs/Long-C/Long-C-r.$i.0.ss.res
done