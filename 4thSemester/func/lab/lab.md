# Programowanie Funkcyjne
## Michał Waluś

### Zadanie 1

```haskell
-- lab1.hs

power :: Int -> Int -> Int
power x y = y ^ x

-- partial application 
p2 = power 4
p3 = power 3
```

$power(x, y) = y^x$ \
$p2(y) = power(4, y) = y^4$ \
$p3(y) = power(3, y) = y^3$

1. Wyznacz wartość `(p2. p3) 2`.
`(p2 . p3) 2` to $p2(p3(2)) = p2(2^3) = (2^3)^4 = 2^{12} = 4096$  

```sh
ghci> (p2 . p3) 2
4096
```

2. Zbadaj typy p2, p3 i (p2 . p3).

```sh
ghci> :t p2
p2 :: Int -> Int
ghci> :t p3
p3 :: Int -> Int
ghci> :t (p2 . p3)
(p2 . p3) :: Int -> Int
```

3. Zapisz powyższe funkcje za pomocą lambda wyrażeń.

``` haskell
(\x y -> y ^ x) -- power 
(\x -> x ^ 4) -- p2
(\x -> x ^ 3) -- p3
(\x -> (x ^ 3) ^ 4) -- (p2 . p3) 
```

### Zadanie 2

Oblicz wartość wyrażeń 2^3^2, (2^3)^2, 2^(2^3).
```sh
ghci> 2^3^2
512
ghci> (2^3)^2
64
ghci> 2^(2^3)
256
```

Sprawdź łączność oraz siłę operatora ^.

```sh
ghci> :i (^)
(^) :: (Num a, Integral b) => a -> b -> a       -- Defined in ‘GHC.Real’
infixr 8 ^
```

Zatem operator ^ ma siłe 8 i łączność prawostroną, tzn. x^y^z = x^(y^z). 

### Zadanie 3

```haskell
-- lab3.hs

f :: Int -> Int
f x = x ^ 2

g :: Int -> Int -> Int
g x y = x + 2 * y

h :: ...
h x y = f(g x y)
```

1. Wyznacz typ h.
h jest typu `Int -> Int -> Int`

```sh
ghci> :t h
h :: Int -> Int -> Int
```

2. Czy h = f . g ?

Jeśli uznajemy operator . za złożenie funkcji to tak, bo $h(x,y) = f(g(x,y))$.
Jednak jeśli spróbujemy sprawdzić typ `(f . g)` w haskellu to otrzymujemy błąd, bo nie możemy złożyć tych dwóch funkcji.

```
ghci> :t (f . g)

<interactive>:1:6: error:
    • Couldn't match type ‘Int -> Int’ with ‘Int’
      Expected: Int -> Int
        Actual: Int -> Int -> Int
    • Probable cause: ‘g’ is applied to too few arguments
      In the second argument of ‘(.)’, namely ‘g’
      In the expression: f . g
```

Zdefiniowanie obu funkcji bez doprecyzowywania typów pozwala nam je złożyć i wtedy h = (f . g).

``` sh
ghci> f x = x ^ 2 
ghci> g x y = x + 2 * y
ghci> :t (f . g)
(f . g) :: (Num a, Num (a -> a)) => a -> a -> a
```

3. Czy h x = f(g x)?

`h x` oraz `g x` są funkcjami, które zwracają funkcje typu `Int -> Int`, natomiast `f` jest funkcją typu `Int -> Int`, czyli jako argument przyjmuje liczbę, a nie funkcję.
Zatem te obiekty nie są równe.

### Zadanie 4

Operacje (+) i (*) jako lambda wyrażeń.

```haskell
(\x y -> x + y) -- +

(\x y -> x * y) -- *
```

### Zadanie 5

$f(x) = 1 + x*(x + 1)$\
$g(x, y) = x + y^2$\
$h(y, x) = x + y^2$

- C++:
```cpp
auto f = [](int x){ return 1 + x * (x + 1); };
auto g = [](int x, int y){ return x + y * y; };
auto h = [](int y, int x){ return x + y * y; };
```

- Python:
```py
f = lambda x : 1 + x * (x + 1)
g = lambda x, y: x + y ** 2
h = lambda y, x: x + y ** 2
```

- JavaScript
```js
const f = (x) => 1 + x * (x + 1)
const g = (x, y) => x + y ^ 2
const h = (y, x) => x + y ^2
```

- Haskell:
```haskell
(\x -> 1 + x * (x + 1)) -- f
(\x y -> x + y^2) -- g
(\y x -> x + y^2) -- h
```

### Zadanie 6

Dane są zbiory $A, B, C$ oraz funkcje curry:\
$curry: C^{B \times A} \rightarrow (C^B)^A$\
$curry(\varphi) = (\lambda a : A \rightarrow (\lambda b : B \rightarrow \varphi (b, a)))$\
i uncurry: \
$uncurry: (C^B)^A \rightarrow C^{B \times A}$\
$uncurry(\psi)(b, a) = (\psi(a))(b)$

1. Niech $\psi \in (C^B)^A$.\
$(curry \circ uncurry)(\psi) = (\lambda a : A \rightarrow (\lambda b : B \rightarrow uncurry(\psi)(b, a))) = (\lambda a : A \rightarrow (\lambda b : B \rightarrow (\psi(a))(b))) = (\lambda a: A \rightarrow \psi(a)) = \psi$\
Zatem $(curry \circ uncurry) = id_{(C^B)^A}$.

Niech $\varphi \in C^{B \times A}$, $x \in A, y \in B$\
$(uncurry \circ curry)(\varphi)(y, x) = uncurry((\lambda a : A \rightarrow (\lambda b : B \rightarrow \varphi (b, a))))(y, x) = ((\lambda a : A \rightarrow (\lambda b : B \rightarrow \varphi (b, a)))(x))(y) = varphi(y, x)$\
Zatem $(uncurry \circ curry) = id_{C^{B \times A}}$
2. curry i uncurry są injekcjami, więc $|(C^B)^A| = |C^{B \times A}|$.
3. Odpowiedniki curry i uncurry w Haskellu

```haskell
-- lab6.hs

curry' :: ((a, b) -> c) -> (b -> (a -> c))
curry' f = (\x -> (\y -> f(y, x)))

uncurry' :: (a -> (b -> c)) -> ((b, a) -> c)
uncurry' f = (\(x, y) -> f y x )
```

### Zadanie 7

```haskell
-- lab7.hs

f1 :: (Int -> Int) -> Int
f1 f = f 0

f2 :: (Int -> Int) -> (Int -> Int)
f2 f= \x -> 2 * f x

f3 :: (Int -> Int) -> (Int -> Int) -> (Int -> Int)
f3 f g = \x -> f x + g x
```

### Zadanie 8

Funkcja, która dla danych $a, b \in \mathbb{R}$ oraz $f \in \mathbb{R}^{\mathbb{R}}$ oblicza $\int_a^b f(x) \,dx$.\
Oznaczmy tą funkcje poprzez I(f, a, b).

Typ I:
```haskell
I :: (Num -> Num) -> Num -> Num -> Num
```
lub
```haskell
I :: ((Num -> Num), Num, Num) -> Num
```

### Zadanie 9

```py
# lab9.py

import math

def f(x): 
    y = math.sin(x)
    return y*y + y + x

def f1(x):
    return (math.sin(x) + 0.5)**2 - 0.25 + x

def sum(n):
    s = 0
    for i in range(n+1):
        s += f(i)
    return s

def sumrec(n, s):
    s += f(n)
    if n == 0:
        return s
    sumrec(n-1, s)
```

### Zadanie 10

Funkcje na listach z Prelude

```haskell
-- lab10.hs

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
```

### Zadanie 11

```haskell
-- lab11.hs

ff = (2 ^)

gg = (^ 2)
```

ff i gg to funkcje przyjmujące jeden argument, ff zwraca 2 do potęgi argumentu, a gg argument do kwadratu.

```sh
ghci> map (^ 2) [1..10]
[1,4,9,16,25,36,49,64,81,100]
ghci> map (2 ^) [1..10]
[2,4,8,16,32,64,128,256,512,1024]
```

Mapujemy obie te funkcje na listę liczb naturalnych od 1 do 10 i otrzymujemy listę pierwszych 10 kwadratów i 10 kolejnych potęg 2.

### Zadanie 12

Przekonwertowanie Integral na Float/Double za pomocą `fromIntegral`.

```
ghci> :i fromIntegral
fromIntegral :: (Integral a, Num b) => a -> b
        -- Defined in ‘GHC.Real’
```

Typ `round`
```
type RealFrac :: * -> Constraint
class (Real a, Fractional a) => RealFrac a where
  ...
  round :: Integral b => a -> b
  ...
```

## Elementy Teorii Liczb

### Zadanie 13

Funkcje $\phi(n)$ oraz $sumphi(n) = \sum_{k|n} \phi(k)$:

```haskell
phin:: Int -> Int -> Int
phin _ 1 = 1
phin n k = 
    if gcd n k == 1 then 1 + phin n (k-1)
    else phin n (k-1)

φ:: Int -> Int
φ n = phin n n

sumphin:: Int -> Int -> Int
sumphin _ 1 = 1
sumphin n k = 
    if mod n k == 0 then φ k + sumphin n (k-1)
    else sumphin n (k-1) 

sumphi:: Int -> Int
sumphi n = sumphin n n

sumphiquick:: Int -> Int
sumphiquick n = n
```

### Zadanie 14

`perfects` zwraca wszystkie liczby doskonałe mniejsze niż n. (bardzo niewydajne)

```haskell
sumdiv :: Int -> Int -> Int
sumdiv _ 1 = 1
sumdiv n k =
    if mod n k == 0 then k + sumdiv n (k-1)
    else sumdiv n (k-1)

perfectsLoop :: Int -> Int -> [Int]
perfectsLoop _ 1 = []
perfectsLoop n k = 
    if sumdiv k (k-1) == k then k:perfectsLoop n (k-1)
    else perfectsLoop n (k-1)

perfects:: Int -> [Int]
perfects n = perfectsLoop n n
```

### Zadanie 15

Liczby zaprzyjaźnione - Amicable numbers

```haskell
sumdivLoop :: Int -> Int -> Int
sumdivLoop _ 0 = 0
sumdivLoop n k =
    if k * k >= n then 0
    else if k == 1 then k + sumdivLoop n (k + 1)
    else if mod n k == 0 then k + (div n k) + sumdivLoop n (k+1)
    else sumdivLoop n (k+1)

sumdiv :: Int -> Int
sumdiv n = sumdivLoop n 1

amicables :: Int -> [(Int, Int)]
amicables 1 = []
amicables n = 
    if sumdiv (sumdiv n) == n && sumdiv n < n then (n, sumdiv n):(amicables (n-1))
    else amicables (n-1)
```
```sh
ghci> amicables (10^5)
[(88730,79750),(87633,69615),(76084,63020),(71145,67095),(66992,66928),(18416,17296),(14595,12285),(10856,10744),(6368,6232),(5564,5020),(2924,2620),(1210,1184),(284,220)]
```

### Zadanie 16

$dcp(n) = \frac{1}{n^2}|\{(k,l)\in\{1,...,n\}^2 : gcd(k, l) = 1\}|$ 

```haskell
dcp :: Int -> Double
dcp n = fromIntegral (length ([(k, l) | k <- [1..n], l <- [1..n], gcd k l == 1])) / fromIntegral n^2

coprime :: Int -> Int -> Int
coprime 1 1 = 1
coprime 2 1 = 3
coprime n 1 = 2 + coprime (n-1) (n-2)
coprime n k = 
    if gcd n k == 1 then 2 + coprime n (k-1)
    else coprime n (k-1)

dcprec :: Int -> Double
dcprec n = fromIntegral (coprime n n) / fromIntegral n ^2
```
$lim_{n\rightarrow \infty} dcp(n) \approx 0.608$

## Listy - Część I

### Zadanie 17

```haskell
nub' [] = []
nub' (x:xs) = x:filter (\y -> y /= x) (nub' xs)
```

### Zadanie 18

```haskell
inits' [] = [[]]
inits' (x:xs) = []:map (x:) (inits' xs)
```

### Zadanie 19

```haskell 
tails' [] = [[]]
tails' (x:xs) = tails' xs ++ [(x:xs)]
```

### Zadanie 20

```haskell
splits' :: [a] -> [([a], [a])]
splits' [] = [([], [])]
splits' (x:xs) = ([], (x:xs)):map (\(y, z) -> (x:y, z)) (splits' xs)
```

### Zadanie 21

```haskell
partition :: (a -> Bool) -> [a] -> ([a], [a])
partition _ [] = ([], [])
partition p (x:xs) = 
    if p x then (x:l, r)
    else (l, x:r)
    where (l,r) = partition p xs
```

### Zadanie 22

```haskell
splits' [] = [([], [])]
splits' (x:xs) = ([], (x:xs)):map (\(y, z) -> (x:y, z)) (splits' xs)

permutations' :: [a] -> [[a]]
permutations' [] = [[]]
permutations' (x:xs) = [y ++ x:z| (y,z) <- concat (map (splits') (permutations' xs))]
```

### Zadanie 23

```haskell
import Data.List (permutations)

f perm = length ([(i,j)| i<-[0..7], j<-[0..7], abs ((-) i j) /= abs ( (-) (perm !! i) (perm !! j) )])
possible = [y| y<-permutations [1..8], f y == 56]

unique [] = []
unique (x:xs) = 
    if reverse x `elem` xs then unique xs
    else if (map (\x -> 9 - x) x) `elem` xs then unique xs
    else if reverse (map (\x -> 9 - x) x) `elem` xs then unique xs
    else x:unique xs
```

### Zadanie 24

```haskell
zeros n 
    | n < 5 = 0
    | otherwise = div n 5 + zeros (div n 5)
```

### Zadanie 25

```haskell
qs :: (Ord a) => [a] -> [a]
qs xs = quicksort xs []
    where
        quicksort [] acc = acc
        quicksort (x:xs) acc = quicksort lesser (x:quicksort greater acc)
            where
                (lesser, greater) = partition (<= x) xs
```

### Zadanie 26

```haskell
isSorted:: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [a] = True
isSorted (x:xs) =
    if x <= head xs then isSorted xs
    else False
```

### Zadanie 27

```haskell
isSorted:: (Ord a) => [a] -> Bool
isSorted [] = True
isSorted [a] = True
isSorted (x:xs) =
    if x <= head xs then isSorted xs
    else False

bubbleLoop [] = []
bubbleLoop [a] = [a]
bubbleLoop (x:y:xs) =
    if x <= y then x:bubbleLoop (y:xs) 
    else y:bubbleLoop (x:xs)

bubbleSort [] = []
bubbleSort [a] = [a]
bubbleSort x =
    if isSorted x then x
    else bubbleSort (bubbleLoop x)
```
Lepszy:
```haskell
bub :: Ord a => [a] -> [a]
bub [] = []
bub [x] = [x]
bub (x:y:xs)
    | x <= y = x:bub (y:xs)
    | otherwise = bub(y:bub(x:xs))
```


### Zadanie 28

```haskell
import Data.List (partition)

inSort []     = []
inSort (x:xs) = l ++ [x] ++ r
                where (l, r) = partition (<x) (inSort xs)

qS [] = []
qS (x:xs) = 
    if length xs > 10 then qS [t| t <- xs, t<=x] ++ x:qS [t|t <- xs, t>x]
    else inSort (x:xs)
```

### Zadanie 29

```haskell
rev :: [a] -> [a]
rev [] = []
rev (x:xs) = (rev xs) ++[x]
```

Złożoność obliczeniowa:

$T(0) = \Theta(1)$<br>
$T(n) = T(n-1) + O(n) = \sum_{i=1}^n O(i) = O\left( \sum_{i=1}^n i \right) = O\left( \frac{n(n+1)}{2} \right) = O(n^2)$

### Zadanie 30

```haskell
filter' p = concat . map box
    where box x = 
            if p x then [x]
            else []
```

### Zadanie 31

```haskell
takeWhile' f [] = []
takeWhile' f (x:xs) =
    if f x then x:takeWhile' f xs
    else [] 

dropWhile' f [] = []
dropWhile' f (x:xs) =
    if f x then dropWhile' f xs
    else (x:xs)
```

### Zadanie 32

```haskell
import Data.List (transpose)

alleq [] = True
alleq [a] = True
alleq (x:xs) =
    if x == head xs then alleq xs
    else False

prefixT [] = []
prefixT (x:xs) =
    if alleq x then head x:prefixT xs 
    else []

prefix x = prefixT (transpose x)
```

### Zadanie 33

```haskell
subCard :: Int -> [a] -> [[a]]
subCard 0 _ = [[]]
subCard _ [] = []
subCard n (x:xs) =
    if n - 1 > length xs then []
    else map (x:) (subCard (n-1) xs) ++ subCard n xs  
```

## Foldy - Część II

### Zadanie 34

```
ghci> :t sum
sum :: (Foldable t, Num a) => t a -> a
ghci> :t product
product :: (Foldable t, Num a) => t a -> a
ghci> :t all
all :: Foldable t => (a -> Bool) -> t a -> Bool
ghci> :t any
any :: Foldable t => (a -> Bool) -> t a -> Bool
```

`sum` - suma listy<br>
`product` - iloczyn listy<br>
`all` - czy wszystkie elementy listy spełniają warunek (funkcję)<br>
`any` - czy jakikolwiek element listy spełnia warunek (funkcję)

### Zadanie 35

```
ghci> foldl (+) 0 [1..10^7]
50000005000000
(7.88 secs, 1,612,375,936 bytes)
ghci> foldr (+) 0 [1..10^7]
50000005000000
(0.74 secs, 1,615,377,312 bytes)
ghci> foldl1 (+) [1..10^7]
50000005000000
(0.94 secs, 1,612,375,840 bytes)
ghci> foldr1 (+) [1..10^7]
50000005000000
(0.76 secs, 1,695,377,200 bytes)
ghci> sum [1..10^7]
50000005000000
(1.01 secs, 880,075,632 bytes)
ghci> foldl' (+) 0 [1..10^7]
50000005000000
(0.16 secs, 880,075,656 bytes)
```

funkcja `foldr'` nie istnieje w `Data.List`

### Zadanie 36

```haskell
reverse' xs = foldl (flip (:)) [] xs
```

```
ghci> take 10 (reverse' [1..10^6])
[1000000,999999,999998,999997,999996,999995,999994,999993,999992,999991]
(0.03 secs, 112,121,184 bytes)
ghci> take 10 (reverse' [1..10^8])
[100000000,99999999,99999998,99999997,99999996,99999995,99999994,99999993,99999992,99999991]
(7.37 secs, 11,200,136,536 bytes)
ghci> take 10 (rev [1..10^6])
[1000000,999999,999998,999997,999996,999995,999994,999993,999992,999991]
(1.31 secs, 1,109,621,440 bytes)
ghci> take 10 (rev [1..10^7])
[10000000,9999999,9999998,9999997,9999996,9999995,9999994,9999993,9999992,9999991]
(13.10 secs, 11,095,717,408 bytes)
```

### Zadanie 37

```haskell
countEven xs = foldr ((+).(\x -> if (even x) then 1 else 0)) 0 xs
```

### Zadanie 38

```haskell
dec2Int xs = foldl (\x y -> 10*x + y) 0 xs
```

### Zadanie 39

`foldl (-) e xs = e - sum xs` jest poprawne 

foldl:

```
        *
       / \
      *  x4
     / \
    *  x3
   / \
  *  x2
 / \
e   x1
```
Co się przekłada na ((((e - x1) - x2) - x3) - x4) = e - x1 - x2 - x3 - x4 = e - (x1 + x2 + x3 + x4) 

### Zadanie 40

```haskell
 addWhenSmaller xs n = xs ++ map (++[n]) (filter (\x -> if (x == []) then True else last x < n) xs)

 longest [x] = x
 longest (x:xs) = 
    if (length x > length l) then x
    else l
    where l = longest xs

 lmss (x:xs) = longest (foldl addWhenSmaller [[x]] xs)
 ```

### Zadanie 41

```haskell
remdupl :: (Foldable t, Eq a) => t a -> [a]
remdupl = foldr (\x y -> if null y then [x] else if x == head y then y else x:y) []
```

### Zadanie 42

```haskell
approx n = foldl (+) 0 (map (\m -> 1 / foldr (*) 1.0 [1..m]) [0..n])
```

### Zadanie 43

```haskell
altsum xs = (-1)^(length xs + 1) * foldl (\x y -> -x + y) 0 xs
```

### Zadanie 44

Używając foldl i sum:
```haskell
avgandvar :: Foldable t => t Double -> (Double, Double)
avgandvar xs = (avg, 1/l * foldl (\x y -> x + (y - avg)^2) 0 xs)
    where 
        avg = 1/l * sum xs
        l = fromIntegral (length xs)
```

### Zadanie 45

```haskell
f 0 0 = 1
f 0 1 = 4
f 1 1 = 2
f 1 0 = 4
f 2 0 = 2
f 2 1 = 3
f 3 0 = 3
f 3 1 = 2
```

### Zadanie 47

```haskell
subsetlist:: Eq a => [a] -> [a] -> Bool
subsetlist [] _ = True
subsetlist (x:xs) ys =
    (x `elem` ys) && subsetlist xs ys
```

### Zadanie 49

```haskell
dotprod :: (Num a) => [a] -> [a] -> a
dotprod xs ys = sum (zipWith (*) xs ys)
```

### Zadanie 50 

```haskell
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
    where m1 = intPowerM m (div k 2)```
```

### Elementy Teorii Kategorii - Część III

### Zadanie 52

Załóżmy, że $Id1_A$ i $Id2_A$ to identyczności, wtedy z własności identyczności:
1. $Id1_A \circ Id2_A = Id1_A$ 
2. $Id1_A \circ Id2_A = Id2_A$ 

Zatem $Id1_A = Id2_A$. $\square$

### Zadanie 53

*Def.* Obiekt $c$ nazywamy końcowym w $\mathcal{C} \equiv (\forall X \in ob(\mathcal{C}))(\exist ! f)(f:X \rightarrow c)$

Niech $c_1, c_2$ są elementami końcowymi.

Zatem $(\exists ! f_1)(f: c_1 \rightarrow c_2)$ oraz $(\exists ! f_2)(f: c_2 \rightarrow c_1)$

Wtedy $f_1 \circ f_2: c_2 \rightarrow c_2$, ale $Id_{c_2}: c_2 \rightarrow c_2$, więc $f_1 \circ f_2 = Id_{c_2}$

Zatem $c_1 \cong c_2$

### Zadanie 54

- Końcowy: Grupa/Pierścień/Monoid trywialny
- Początkowy: 