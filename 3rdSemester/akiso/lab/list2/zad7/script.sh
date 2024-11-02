for filename in *; do fn="$filename" && fn2="$(echo $filename | tr [:upper:] [:lower:])" && mv ./"$fn" ./"$fn2"; done 
