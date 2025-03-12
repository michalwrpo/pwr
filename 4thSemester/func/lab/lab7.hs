f1 :: (Int -> Int) -> Int
f1 f = f 0

f2 :: (Int -> Int) -> (Int -> Int)
f2 f= \x -> 2 * f x

f3 :: (Int -> Int) -> (Int -> Int) -> (Int -> Int)
f3 f g = \x -> f x + g x