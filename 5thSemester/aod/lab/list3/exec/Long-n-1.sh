for i in {10..21}; do
    ./app.out dijkstra -d inputs/Long-n/Long-n.$i.0.gr -ss inputs/Long-n/Long-n.$i.1.ss -oss outputs/Long-n/Long-n-d.$i.1.ss.res
    ./app.out dial -d inputs/Long-n/Long-n.$i.0.gr -ss inputs/Long-n/Long-n.$i.1.ss -oss outputs/Long-n/Long-n-l.$i.1.ss.res
    ./app.out radixheap -d inputs/Long-n/Long-n.$i.0.gr -ss inputs/Long-n/Long-n.$i.1.ss -oss outputs/Long-n/Long-n-r.$i.1.ss.res
done