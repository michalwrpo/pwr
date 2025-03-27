partition :: (a -> Bool) -> [a] -> ([a], [a])
partition _ [] = ([], [])
partition p (x:xs) = if p x then (x:l, r)
                            else (l, x:r)
                        where (l, r) = partition p xs

qs :: (Ord a) => [a] -> [a]
qs xs = quicksort xs []
    where
        quicksort [] acc = acc
        quicksort (x:xs) acc = quicksort lesser (x:quicksort greater acc)
            where
                (lesser, greater) = partition (<= x) xs