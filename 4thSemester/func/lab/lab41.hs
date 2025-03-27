remdupl :: (Foldable t, Eq a) => t a -> [a]
remdupl = foldr (\x y -> if null y then [x] else if x == head y then y else x:y) []