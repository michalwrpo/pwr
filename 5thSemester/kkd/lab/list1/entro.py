from sys import argv
from math import log2

def entropy(data:bytearray) -> float:
    if not data:
        return 0.0

    freq = [0] * 256
    for byte in data:
        freq[byte] += 1

    ent = 0.0
    length = len(data)

    for count in freq:
        if count > 0:
            p = count / length
            ent -= p * log2(p)

    return ent

def conditionalEntropy(data:bytearray) -> float:
    if not data:
        return 0.0

    pair_freq = {}
    pair_freq[(0, data[0])] = 1
    single_freq = [0] * 256

    for i in range(len(data) - 1):
        pair = (data[i], data[i + 1])
        if pair not in pair_freq:
            pair_freq[pair] = 0
        pair_freq[pair] += 1
        single_freq[data[i]] += 1

    single_freq[data[-1]] += 1

    cond_ent = 0.0
    length = len(data) - 1

    entropies = [0.0] * 256
    for (_, y), count in pair_freq.items():
        p_xy = count / length
        entropies[y] -= (p_xy) * log2(p_xy)

    for x in range(256):
        p_x = single_freq[x] / len(data)
        cond_ent += p_x * entropies[x]

    return cond_ent

if __name__ == "__main__":
    if len(argv) != 2:
        print("Usage: python entro.py <filename>")
        exit(1)

    filename = argv[1]

    with open(filename, "rb") as f:
        data = bytearray(f.read())
        print(f"Entropy: {entropy(data)}")
        print(f"Conditional Entropy: {conditionalEntropy(data)}")
        print(f"Difference: {entropy(data) - conditionalEntropy(data)}")
        