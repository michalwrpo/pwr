splits' [] = [([], [])]
splits' (x:xs) = ([], x:xs):map (\(y, z) -> (x:y, z)) (splits' xs)

permutations' :: [a] -> [[a]]
permutations' [] = [[]]
permutations' (x:xs) = [y ++ x:z| (y,z) <- concat (map (splits') (permutations' xs))]