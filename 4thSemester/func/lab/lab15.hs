sumdivLoop :: Int -> Int -> Int
sumdivLoop _ 0 = 0
sumdivLoop n k =
    if k * k >= n then 0
    else if k == 1 then 1 + sumdivLoop n 2
    else if mod n k == 0 then k + (div n k) + sumdivLoop n (k+1)
    else sumdivLoop n (k+1)

sumdiv :: Int -> Int
sumdiv n = sumdivLoop n 1

amicables :: Int -> [(Int, Int)]
amicables 1 = []
amicables n = 
    if sumdiv (sumdiv n) == n && sumdiv n < n then (n, sumdiv n):(amicables (n-1))
    else amicables (n-1)

