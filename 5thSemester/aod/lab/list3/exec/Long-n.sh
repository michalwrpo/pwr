for i in {10..21}; do
    ./app.out dijkstra -d inputs/Long-n/Long-n.$i.0.gr -ss inputs/Long-n/Long-n.$i.0.ss -oss outputs/Long-n/Long-n-d.$i.0.ss.res
    ./app.out dial -d inputs/Long-n/Long-n.$i.0.gr -ss inputs/Long-n/Long-n.$i.0.ss -oss outputs/Long-n/Long-n-l.$i.0.ss.res
    ./app.out radixheap -d inputs/Long-n/Long-n.$i.0.gr -ss inputs/Long-n/Long-n.$i.0.ss -oss outputs/Long-n/Long-n-r.$i.0.ss.res
done