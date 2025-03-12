curry' :: ((a, b) -> c) -> (b -> (a -> c))
curry' f = (\x -> (\y -> f(y, x)))

uncurry' :: (a -> (b -> c)) -> ((b, a) -> c)
uncurry' f = (\(x, y) -> f y x )


-- for tests
g :: (Int, Int) -> Int
g(x, y) = x - y
h :: Int -> Int -> Int
h x y = x - y