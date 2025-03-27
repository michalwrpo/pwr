dec2Int :: [Integer] -> Integer
dec2Int = foldl (\x y -> 10*x + y) 0