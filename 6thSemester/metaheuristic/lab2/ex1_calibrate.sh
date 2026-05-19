# FILES=(wi29.tsp dj38.tsp qa194.tsp uy734.tsp zi929.tsp mu1979.tsp ca4663.tsp tz6117.tsp eg7146.tsp ei8246.tsp)
FILES=(wi29.tsp dj38.tsp qa194.tsp uy734.tsp zi929.tsp)
TEMPS=(1500 1800 1900 2000 2500)

echo "" > calibration_results.txt

for temp in ${TEMPS[@]}; do
    for cooling in {80..99}; do
    echo "Temp $temp Cooling $cooling" >> calibration_results.txt

    ./app.out 1 "data/zi929.tsp" 420 $temp 0.$cooling > ex1_out/"$(basename $FILE .tsp).out"

    ./print1.sh >> calibration_results.txt
    echo "-----------------------" >> calibration_results.txt
    done
done

# for attempts in {20..500..20}; do
#     echo "Attempts $attempts" >> calibration_results.txt

#     for FILE in ${FILES[@]}; do
#         ./app.out 1 "data/$FILE" $attempts 500 0.9 > ex1_out/"$(basename $FILE .tsp).out"
#     done

#     ./print1.sh >> calibration_results.txt
#     echo "-----------------------" >> calibration_results.txt
# done

# for cooling in {87..91}; do
#     echo "Cooling $cooling" >> calibration_results.txt

#     for FILE in ${FILES[@]}; do
#         ./app.out 1 "data/$FILE" 420 500 0.$cooling > ex1_out/"$(basename $FILE .tsp).out"
#     done

#     ./print1.sh >> calibration_results.txt
#     echo "-----------------------" >> calibration_results.txt
# done