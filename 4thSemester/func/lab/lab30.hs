takeWhile' f [] = []
takeWhile' f (x:xs) =
    if f x then x:takeWhile' f xs
    else [] 

dropWhile' f [] = []
dropWhile' f (x:xs) =
    if f x then dropWhile' f xs
    else (x:xs)