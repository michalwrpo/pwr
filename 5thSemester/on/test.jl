"""Sieve of Eratosthenes function docstring"""
function es(n::Int) # accepts one integer argument
    isprime = trues(n) # n-element vector of true-s
    isprime[1] = false # 1 is not a prime
    for i in 2:isqrt(n) # loop integers less or equal than sqrt(n)
        if isprime[i] # conditional evaluation
            for j in i^2:i:n # sequence with step i
                isprime[j] = false
            end
        end
    end
    return filter(x -> isprime[x], 1:n) # filter using an anonymous function
end

# println(es(100)) # print all primes less or equal than 100
# @time length(es(10^6)) # check function execution time and memory usage

function plusOne(n::Int)
    return n + n * 1/n
end

# println(plusOne(5))

function ⊕(n::Int, m::Int)
    return n * m + n
end

println(5 ⊕ 3)