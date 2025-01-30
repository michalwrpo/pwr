import random
from typing import Iterator

# LCG from https://github.com/rossilor95/lcg-python
def linear_congruential_generator(m: int, a: int, c: int, seed: int) -> Iterator[int]:
    """
    This generator implements the Linear Congruential Generator algorithm
    :param m: the modulus, a positive integer constant
    :param a: the multiplier, a non-negative integer constant < m
    :param c: the increment, a non-negative integer constant < m
    :param seed: the starting state of the LCG. It is used to initialize the pseudo-random number sequence
    :return: a non-negative integer in [0, m-1] representing the i-th state of the generator
    """
    x = seed
    while True:
        yield x
        x = (a * x + c) % m


if __name__=="__main__":
    file = open("ex4.txt", 'w')

    # Mersenne twister
    for i in range(10):
        num = random.getrandbits(10000)
        file.write(f'{num:10000b}'.replace(" ", "0"))
    file.write("\n\n")

    lcg = linear_congruential_generator(4_294_967_295, 213_543_091, 0, 123_534_765)
    next(lcg)
    next(lcg)
    for i in range(3000):
        file.write(f'{next(lcg):32b}'.replace(" ", "0"))

    file.close()