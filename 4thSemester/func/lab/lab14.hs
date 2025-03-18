sumdiv :: Int -> Int -> Int
sumdiv _ 1 = 1
sumdiv n k =
    if mod n k == 0 then k + sumdiv n (k-1)
    else sumdiv n (k-1)

perfectsLoop :: Int -> Int -> [Int]
perfectsLoop _ 1 = []
perfectsLoop n k = 
    if sumdiv k (k-1) == k then k:perfectsLoop n (k-1)
    else perfectsLoop n (k-1)

perfects:: Int -> [Int]
perfects n = perfectsLoop n n