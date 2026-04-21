# FILES=(wi29.tsp dj38.tsp qa194.tsp uy734.tsp zi929.tsp mu1979.tsp ca4663.tsp tz6117.tsp eg7146.tsp ei8246.tsp)
FILES=(wi29.tsp dj38.tsp qa194.tsp uy734.tsp zi929.tsp)

for FILE in ${FILES[@]}; do
    echo "Processing $FILE"
    time ./app.out 2 "data/$FILE" > ex2_out/"$(basename $FILE .tsp).out"
done