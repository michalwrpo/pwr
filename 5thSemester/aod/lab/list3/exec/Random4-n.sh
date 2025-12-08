for i in {10..21}; do
    ./app.out dijkstra -d inputs/Random4-n/Random4-n.$i.0.gr -ss inputs/Random4-n/Random4-n.$i.0.ss -oss outputs/Random4-n/Random4-n-d.$i.0.ss.res
    ./app.out dial -d inputs/Random4-n/Random4-n.$i.0.gr -ss inputs/Random4-n/Random4-n.$i.0.ss -oss outputs/Random4-n/Random4-n-l.$i.0.ss.res
    ./app.out radixheap -d inputs/Random4-n/Random4-n.$i.0.gr -ss inputs/Random4-n/Random4-n.$i.0.ss -oss outputs/Random4-n/Random4-n-r.$i.0.ss.res
done