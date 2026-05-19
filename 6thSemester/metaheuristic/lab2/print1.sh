for file in ex1_out/*; do
    echo -n "$(basename "$file") - "
    grep "Best solution" "$file"
done