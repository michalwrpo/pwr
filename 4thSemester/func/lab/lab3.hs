f :: Int -> Int
f x = x ^ 2

g :: Int -> Int -> Int
g x y = x + 2 * y

h :: Int -> Int -> Int
h x y = f(g x y)
