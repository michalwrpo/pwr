isSorted:: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [a] = True
isSorted (x:xs) =
    if x <= head xs then isSorted xs
    else False