partition :: (a -> Bool) -> [a] -> ([a], [a])
partition _ [] = ([], [])
partition p (x:xs) = 
    if p x then (x:l, r)
    else (l, x:r)
    where (l,r) = partition p xs