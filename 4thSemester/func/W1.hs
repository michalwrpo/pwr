fact1 n = if n == 0 then 1
          else  n * (fact1 (n-1) ) 

fact2::Integer -> Integer
fact2 0 = 1
fact2 n = n * fact2(n-1)