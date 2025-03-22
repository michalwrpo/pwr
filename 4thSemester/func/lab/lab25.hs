import Data.List (partition)

qs [] = []
qs (x:xs) = qs [t| t <- xs, t<=x] ++ [x] ++ qs [t|t <- xs, t>x]

inSort []     = []
inSort (x:xs) = l ++ [x] ++ r
                where (l, r) = partition (<x) (inSort xs)

qS [] = []
qS (x:xs) = 
    if length xs > 5 then qS [t| t <- xs, t<=x] ++ x:qS [t|t <- xs, t>x]
    else inSort (x:xs)