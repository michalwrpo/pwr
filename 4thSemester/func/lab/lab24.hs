zeros n 
    | n == 0 = 1
    | n < 5 = 0
    | otherwise = div n 5 + zeros (div n 5)