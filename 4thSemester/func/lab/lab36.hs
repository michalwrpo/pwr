reverse' :: Foldable t => t a -> [a]
reverse' = foldl (flip (:)) []

rev :: [a] -> [a]
rev [] = []
rev (x:xs) = rev xs ++[x]