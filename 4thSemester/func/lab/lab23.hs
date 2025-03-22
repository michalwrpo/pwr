import Data.List (permutations)

f perm = length ([(i,j)| i<-[0..7], j<-[0..7], abs ((-) i j) /= abs ( (-) (perm !! i) (perm !! j) )])
possible = [y| y<-permutations [1..8], f y == 56]

unique [] = []
unique (x:xs) = 
    if reverse x `elem` xs then unique xs
    else if (map (\x -> 9 - x) x) `elem` xs then unique xs
    else if reverse (map (\x -> 9 - x) x) `elem` xs then unique xs
    else x:unique xs