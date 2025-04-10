isSorted:: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [a] = True
isSorted (x:xs) =
    (x <= head xs) && isSorted xs

bubbleLoop [] = []
bubbleLoop [a] = [a]
bubbleLoop (x:y:xs) =
    if x <= y then x:bubbleLoop (y:xs)
    else y:bubbleLoop (x:xs)

bubbleSort [] = []
bubbleSort [a] = [a]
bubbleSort x =
    if isSorted x then x
    else bubbleSort (bubbleLoop x)

bub :: Ord a => [a] -> [a]
bub [] = []
bub [x] = [x]
bub (x:y:xs)
    | x <= y = x:bub (y:xs)
    | otherwise = bub (y:bub (x:xs))