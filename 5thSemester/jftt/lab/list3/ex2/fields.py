class Z:
    def __init__(self, n, powRing = None):
        self.N = n
        self.powRing = powRing

    def num(self, a):
        return (a % self.N + self.N) % self.N

    def add(self, a, b):
        return (a + b) % self.N
    
    def sub(self, a, b):
        return (a - b + self.N) % self.N
    
    def mul(self, a, b):
        return (a * b) % self.N
    
    def inverse(self, a):
        prev_r = a
        r = self.N
        prev_s = 1
        s = 0
        prev_t = 0
        t = 1
        while r != 0:
            q = prev_r // r
            prev_r, r = r, prev_r - q * r
            prev_s, s = s, prev_s - q * s
            prev_t, t = t, prev_t - q * t
        
        if prev_r != 1:
            raise ValueError("Division not possible, inverse does not exist.")
        else:
            return prev_s % self.N
        
    def div(self, a, b):
        b_inv = self.inverse(b)
        return self.mul(a, b_inv)
    
    def pow(self, a, exp):
        if self.powRing == None:
            raise ValueError("Power ring not defined.")
        result = 1
        base = a % self.N
        exponent = exp
        while exponent > 0:
            if (exponent % 2) == 1:
                result = (result * base) % self.N
            exponent = exponent >> 1
            base = (base * base) % self.N
        return result
