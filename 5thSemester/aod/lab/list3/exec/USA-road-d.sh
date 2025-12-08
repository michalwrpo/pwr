#!/bin/bash

REGIONS=(
    BAY COL E LKS NW USA
    CAL CTR FLA NE NY W
)

for r in "${REGIONS[@]}"; do
    ./app.out dijkstra  -d inputs/USA-road-d/USA-road-d.$r.gr -ss inputs/USA-road-d/USA-road-d.$r.ss  -oss outputs/USA-road-d/USA-road-d-d.$r.0.ss.res
    ./app.out dial      -d inputs/USA-road-d/USA-road-d.$r.gr -ss inputs/USA-road-d/USA-road-d.$r.ss  -oss outputs/USA-road-d/USA-road-d-l.$r.0.ss.res
    ./app.out radixheap -d inputs/USA-road-d/USA-road-d.$r.gr -ss inputs/USA-road-d/USA-road-d.$r.ss  -oss outputs/USA-road-d/USA-road-d-r.$r.0.ss.res
done
