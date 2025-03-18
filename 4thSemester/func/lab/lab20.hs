splits' :: [a] -> [([a], [a])]
splits' [] = [([], [])]
splits' (x:xs) = ([], (x:xs)):map (\(y, z) -> (x:y, z)) (splits' xs)