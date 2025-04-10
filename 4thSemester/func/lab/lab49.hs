dotprod :: (Num a) => [a] -> [a] -> a
dotprod xs ys = sum (zipWith (*) xs ys)