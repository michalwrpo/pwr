{-
    file = w2.hs
    author = JCi
    date = 11.03.2025
-}

module W2 where

id' x = x

coll n | n == 1 = 1
       | even n = coll(div n 2)
       | otherwise = coll(3*n + 1)

collatz :: (Int, Int) -> (Int, Int)
collatz (n, s) | n == 1 = (1, s)
              | even n = collatz(div n 2, s+1)
              | otherwise = collatz(3*n + 1, s+1)

loz n = snd(collatz(n, 0))