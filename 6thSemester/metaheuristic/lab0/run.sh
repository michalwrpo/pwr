DATA=("dj38.tsp" "qa194.tsp" "uy734.tsp" "wi29.tsp" "zi929.tsp")

# for file in "${DATA[@]}"; do
#     python tsp_random.py "$file"
# done

for file in "${DATA[@]}"; do
    python mst.py "$file" > "$file".mst
done