{-
    info: Wykład z FP 2024/25 lato
    autor: Jacek Cichoń
    data: 18.03.2025
-}

module W3 where

{- SORTOWANIA -}
-- quicksort
qS [] = []
qS (x:xs) = (qS [y| y <- xs, y < x]) ++
            [x] ++
            (qS [y| y <- xs, y >= x])

-- partition
partition :: (a -> Bool) -> [a] -> ([a], [a])
partition _ [] = ([], [])
partition p (x:xs) = if p x then (x:l, r)
                            else (l, x:r)
                        where (l, r) = partition p xs

-- qSort 
qSort []     = []
qSort [x]    = [x]
qSort (x:xs) = (qSort l) ++ [x] ++ (qSort r)
               where (l, r) = partition (<x) xs

-- inSort
inSort []     = []
inSort (x:xs) = l ++ [x] ++ r
                where sxs = inSort xs
                      (l, r) = partition (<x) sxs

-- mergeSort (zadanie)

-- zip
zip' [] _ = []
zip' _ [] = []
zip' (x:xs) (y:ys) = (x,y):(zip' xs ys)

add [] = 0
add (x:xs) = x + add xs

-- product
pro [] = 1
pro (x:xs) = x * pro xs

myfoldr op e [] = e
myfoldr op e (x:xs) = op x (myfoldr op e xs)

myfoldl op e [] = e 
myfoldl op e (x:xs) = myfoldl op (op e x) xs