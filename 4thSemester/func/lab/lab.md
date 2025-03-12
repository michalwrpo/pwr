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