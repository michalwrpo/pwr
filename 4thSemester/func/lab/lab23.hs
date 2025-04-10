import Data.List (permutations)

f perm = length ([(i,j)| i<-[0..7], j<-[0..7], abs ((-) i j) /= abs ( (-) (perm !! i) (perm !! j) )])
possible = [y| y<-permutations [1..8], f y == 56]

unique [] = []
unique (x : xs)
  | reverse x `elem` xs = unique xs
  | map (9 -) x `elem` xs = unique xs
  | reverse (map (9 -) x) `elem` xs = unique xs
  | otherwise = x:unique xs