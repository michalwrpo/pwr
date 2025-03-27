import Data.List (transpose)

alleq [] = True
alleq [a] = True
alleq (x:xs) = (x == head xs) && alleq xs

prefixT [] = []
prefixT (x:xs) =
    if alleq x then head x:prefixT xs
    else []

prefix x = prefixT (transpose x)
