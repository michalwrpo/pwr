countEven :: (Foldable t, Integral a, Num b) => t a -> b
countEven = foldr ((+).(\x -> if even x then 1 else 0)) 0