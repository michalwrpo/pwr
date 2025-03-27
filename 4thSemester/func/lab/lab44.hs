avgandvar :: Foldable t => t Double -> (Double, Double)
avgandvar xs = (avg, 1/l * foldl (\x y -> x + (y - avg)^2) 0 xs)
    where 
        avg = 1/l * sum xs
        l = fromIntegral (length xs)

