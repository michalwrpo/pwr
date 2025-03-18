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