for file in ex2_out/*; do
    echo -n "$(basename "$file") - "
    grep "Average steps" "$file"
done