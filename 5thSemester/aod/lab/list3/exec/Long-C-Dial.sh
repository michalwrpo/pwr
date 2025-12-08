for i in {12..15}; do
    ./app.out dial -d inputs/Long-C/Long-C.$i.0.gr -ss inputs/Long-C/Long-C.ss -oss outputs/Long-C/Long-C-l.$i.0.ss.res
    ./app.out dial -d inputs/Long-C/Long-C.$i.0.gr -ss inputs/Long-C/Long-C-1.ss -oss outputs/Long-C/Long-C-l.$i.1.ss.res
done