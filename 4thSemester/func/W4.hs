module W4 where

import Data.List

sum' :: (Foldable t, Num a) => t a -> a
sum' xs = foldl (+) 0 xs
product' :: (Foldable t, Num a) => t a -> a
product'     xs = foldl (*) 1 xs
minimum' :: (Foldable t, Ord a) => t a -> a
minimum'     xs = foldl1 min xs
maximum' :: (Foldable t, Ord a) => t a -> a
maximum'     xs = foldl1 max xs
and' :: Foldable t => t Bool -> Bool
and'         xs = foldl (&&) True xs
or' :: Foldable t => t Bool -> Bool
or'          xs = foldl (||) False xs
concat' :: Foldable t => t [a] -> [a]
concat'      xs = foldl (++) [] xs
concatMap' :: Foldable t => ([a] -> [a]) -> t [a] -> [a]
concatMap' f xs = foldl ((++).f) [] xs

-- Automat deterministyczny
runDFA = foldl