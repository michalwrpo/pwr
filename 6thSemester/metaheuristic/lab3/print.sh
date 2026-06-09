for file in ex4_out/*; do
    echo -n "$(basename "$file") - "
    grep "Average solution" "$file"
done