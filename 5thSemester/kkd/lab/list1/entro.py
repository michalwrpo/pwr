from sys import argv
from math import log2
from collections import defaultdict, Counter
from typing import Dict, Tuple

def entropy(frequencies:Dict[int, float]) -> float:
    if not frequencies:
        return -1.0

    ent = 0.0

    for _, p in frequencies.items():
        ent -= p * log2(p)

    return ent

def conditionalEntropy(frequencies:Dict[int, float], probabilities:Dict[Tuple, float]) -> float:
    if not frequencies or not probabilities:
        return -1.0

    entropies = defaultdict(float)

    for (condition, _), p in probabilities.items():
        entropies[condition] -= p * log2(p)

    cond_ent = 0.0

    for condition, p in frequencies.items():
        cond_ent += p * entropies[condition]

    return cond_ent

if __name__ == "__main__":
    if len(argv) != 2:
        print("Usage: python entro.py <filename>")
        exit(1)

    filename = argv[1]

    with open(filename, "rb") as f:
        data = bytearray(f.read())

        frequencies = dict(Counter(data))
        for k in frequencies.keys():
            frequencies[k] /= len(data)

        pairs = defaultdict(int)
        pairs[(0, data[0])] = 1
        as_first = defaultdict(int)
        as_first[0] = 1

        for i in range(len(data) - 1):
            pairs[(data[i], data[i + 1])] += 1
            as_first[data[i]] += 1

        probabilities = {(condition, value): count / as_first[condition] for (condition, value), count in pairs.items()}

        # print("Frequencies:")
        # for byte, freq in frequencies.items():
        #     print(f"{byte:08b}: {freq}")
        # print(f"Probabilities: {probabilities}")

        ent = entropy(frequencies)
        cond_ent = conditionalEntropy(frequencies, probabilities)

        print(f"Entropy: {ent:8f}")
        print(f"Conditional Entropy: {cond_ent:8f}")
        print(f"Difference: {ent - cond_ent:8f}")
        