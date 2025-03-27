reverse' xs = foldl (flip (:)) [] xs

rev :: [a] -> [a]
rev [] = []
rev (x:xs) = (rev xs) ++[x]