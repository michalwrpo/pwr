for i in {10..21}; do
    ./app.out dijkstra -d inputs/Square-n/Square-n.$i.0.gr -ss inputs/Square-n/Square-n.$i.1.ss -oss outputs/Square-n/Square-n-d.$i.1.ss.res
    ./app.out dial -d inputs/Square-n/Square-n.$i.0.gr -ss inputs/Square-n/Square-n.$i.1.ss -oss outputs/Square-n/Square-n-l.$i.1.ss.res
    ./app.out radixheap -d inputs/Square-n/Square-n.$i.0.gr -ss inputs/Square-n/Square-n.$i.1.ss -oss outputs/Square-n/Square-n-r.$i.1.ss.res
done