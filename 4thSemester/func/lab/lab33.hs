subCard :: Int -> [a] -> [[a]]
subCard 0 _ = [[]]
subCard _ [] = []
subCard n (x:xs) =
    if n - 1 > length xs then []
    else map (x:) (subCard (n-1) xs) ++ subCard n xs  