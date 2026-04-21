FILES=(wi29.tsp dj38.tsp qa194.tsp uy734.tsp zi929.tsp)

for FILE in ${FILES[@]}; do
    echo "Processing $FILE"
    time ./app.out 3 "data/$FILE" > ex3_out/"$(basename $FILE .tsp).out"
done