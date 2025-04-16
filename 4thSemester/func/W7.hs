import Data.List
import Test.QuickCheck

primeQ n = length ([k | k<-[1..n], n `mod` k == 0]) == 2

eulerPoly n = n*n + n + 41

checkEulerPoly' :: Int -> Bool
checkEulerPoly' n = primeQ (eulerPoly n)

checkEuler' = quickCheck checkEulerPoly'

split1 :: Char -> String -> [String]
split1 c [] = []
split1 c xs =
    let x1 = takeWhile (/= c) xs
        x2 = dropWhile (/= c) xs in
    x1 : if null x2 then []
         else split1 c (tail x2)

unsplit :: Char -> [String] -> String
unsplit c wx = intercalate [c] wx 

propSplit1 c xs = unsplit c (split1 c xs) == xs
checkSplit1 = quickCheck (withMaxSuccess 1000 propSplit1)

split :: Char -> String -> [String]
split c "" = [""]
split c xs =
    let x1 = takeWhile (/= c) xs
        x2 = dropWhile (/= c) xs in
    x1 : if null x2 then []
         else split c (tail x2)

checkSplit c xs = 
    let ys = split c xs in
        collect (length ys) (unsplit c ys == xs) 

testSplit = quickCheck (withMaxSuccess 100000 checkSplit)