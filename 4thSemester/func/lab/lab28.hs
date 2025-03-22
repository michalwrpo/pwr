import Data.List (partition)

inSort []     = []
inSort (x:xs) = l ++ [x] ++ r
                where (l, r) = partition (<x) (inSort xs)

qS [] = []
qS (x:xs) = 
    if length xs > 10 then qS [t| t <- xs, t<=x] ++ x:qS [t|t <- xs, t>x]
    else inSort (x:xs)