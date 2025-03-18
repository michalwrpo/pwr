nub' [] = []
nub' (x:xs) = x:filter (\y -> y /= x) (nub' xs)
