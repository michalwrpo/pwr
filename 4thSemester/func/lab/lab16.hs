dcp :: Int -> Double
dcp n = fromIntegral (length ([(k, l) | k <- [1..n], l <- [1..n], gcd k l == 1])) / fromIntegral n^2

coprime :: Int -> Int -> Int
coprime 1 1 = 1
coprime 2 1 = 3
coprime n 1 = 2 + coprime (n-1) (n-2)
coprime n k = 
    if gcd n k == 1 then 2 + coprime n (k-1)
    else coprime n (k-1)

dcprec :: Int -> Double
dcprec n = fromIntegral (coprime n n) / fromIntegral n ^2
