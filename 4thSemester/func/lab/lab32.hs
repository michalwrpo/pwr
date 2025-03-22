import Data.List (transpose)

alleq [] = True
alleq [a] = True
alleq (x:xs) =
    if x == head xs then alleq xs
    else False

prefixT [] = []
prefixT (x:xs) =
    if alleq x then head x:prefixT xs 
    else []

prefix x = prefixT (transpose x)
