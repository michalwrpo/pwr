isSorted:: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [a] = True
isSorted (x:xs) =
    if x <= head xs then isSorted xs
    else False

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