map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f a = f (head a):((map' f) (tail a))

zip' :: [a] -> [b] -> [(a, b)]
zip' [] _ = []
zip' _ [] = []
zip' a b = (head a, head b):zip' (tail a) (tail b)

zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith' _ [] _ = []
zipWith' _ _ [] = []
zipWith' f a b = f (head a) (head b):zipWith' f (tail a) (tail b)

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ [] = []
filter' f a
    | f (head a) = head a:filter' f (tail a)
    | otherwise = filter' f (tail a)

take' :: Int -> [a] -> [a]
take' _ [] = []
take' n a 
    | n < 1 = []
    | otherwise = head a:take' (n-1) (tail a)

drop' :: Int -> [a] -> [a]
drop' _ [] = []
drop' n a
    | n < 1 = a
    | otherwise = drop' (n-1) (tail a)