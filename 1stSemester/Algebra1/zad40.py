

def exEuclidean(a, b):
    x, prev_x, y, prev_y = 0, 1, 1, 0
    while b != 0:
        q = a//b
        a, b = b, a % b
        x, prev_x = prev_x - q * x, x
        y, prev_y = prev_y - q * y, y
    return a, prev_x, prev_y

a = 5
b = 15
print(exEuclidean(a, b))