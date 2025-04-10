 addWhenSmaller xs n = xs ++ map (++[n]) (filter (\x -> null x || (last x < n)) xs)

 longest [x] = x
 longest (x:xs) =
    if length x > length l then x
    else l
    where l = longest xs

 lmss (x:xs) = longest (foldl addWhenSmaller [[x]] xs)