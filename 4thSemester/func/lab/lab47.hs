subsetlist:: Eq a => [a] -> [a] -> Bool
subsetlist [] _ = True
subsetlist (x:xs) ys =
    (x `elem` ys) && subsetlist xs ys