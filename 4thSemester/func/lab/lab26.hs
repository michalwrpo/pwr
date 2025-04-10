isSorted:: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [a] = True
isSorted (x:xs) =
    (x <= head xs) && isSorted xs