for i in {0..15}; do
    # ./app.out dijkstra -d inputs/Square-C/Square-C.$i.0.gr -ss inputs/Square-C/Square-C.ss -oss outputs/Square-C/Square-C-d.$i.0.ss.res
    ./app.out dial -d inputs/Square-C/Square-C.$i.0.gr -ss inputs/Square-C/Square-C.ss -oss outputs/Square-C/Square-C-l.$i.0.ss.res
    # ./app.out radixheap -d inputs/Square-C/Square-C.$i.0.gr -ss inputs/Square-C/Square-C.ss -oss outputs/Square-C/Square-C-r.$i.0.ss.res
done