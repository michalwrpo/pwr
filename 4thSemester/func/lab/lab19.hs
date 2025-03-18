tails' [] = [[]]
tails' (x:xs) = tails' xs ++ [(x:xs)]