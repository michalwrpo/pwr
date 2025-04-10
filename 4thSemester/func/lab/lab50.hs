module Matrix (Matrix, addM, multM, intPowerM, dims) where
import Data.List

type Matrix a = [[a]]

dims :: Num a => Matrix a -> (Int , Int)
dims m = (length (head m), length m)

addM :: Num a => Matrix a -> Matrix a -> Matrix a
addM = zipWith (zipWith (+))

multRow :: Num a => Matrix a -> Matrix a -> [a]
multRow _ [] = []
multRow m1 m2 = sum (zipWith (*) (head m1) (head m2)) : multRow m1 (tail m2)

multM :: Num a => Matrix a -> Matrix a -> Matrix a
multM [] _ = []
multM m1 m2 = multRow m1 (transpose m2) : multM (tail m1) m2 

intPowerM :: Num a => Matrix a -> Int -> Matrix a
intPowerM m 1 = m
intPowerM m k =
    if even k then multM m1 m1
    else multM m (multM m1 m1)
    where m1 = intPowerM m (div k 2)