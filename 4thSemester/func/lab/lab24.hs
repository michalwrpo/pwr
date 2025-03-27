zeros n 
    | n < 5 = 0
    | otherwise = div n 5 + zeros (div n 5)