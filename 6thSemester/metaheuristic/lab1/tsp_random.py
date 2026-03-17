from typing import List, Tuple
import sys
import numpy as np
from matplotlib import pyplot as plt

def load_data(filename: str) -> List[Tuple[float, float]]:
    parsed = []

    with open(filename, 'r') as file:
        data = file.read().split("\n")
        for line in data:
            if line == "" or line[0].isalpha():
                continue

            split = line.split(" ")
            entry = (float(split[1]), float(split[2]))

            parsed.append(entry)

    return parsed

def calculate_len(path: np.ndarray) -> int:
    distance = 0
    nodes_no = len(path)

    if nodes_no < 2:
        return 0
    
    for i in range(nodes_no):
        next_i = (i + 1) % nodes_no
        distance += round(np.sqrt((path[i][0] - path[next_i][0]) ** 2 + (path[i][1] - path[next_i][1]) ** 2))

    return distance

def plot_solution(order: np.ndarray, filename: str):
    plt.plot([point[0] for point in order], [point[1] for point in order], marker=".", linewidth=1, markersize=7)
    plt.title(f"{filename} - the best solution found")
    plt.grid()

    outname = filename.split(".")[0] + ".png"
    plt.savefig(outname)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Input filename not given.")
        sys.exit(1)

    permutation_no = 1000
    size1 = 10
    size2 = 100

    outfile = open(sys.argv[1].split(".")[0] + ".txt", "w")

    rng = np.random.default_rng()
    data = load_data(sys.argv[1])
    results = []
    best = np.array(data)
    best_len = 10**20

    for _ in range(permutation_no):
        permutation = rng.permutation(data)
        permutation = np.append(permutation, [permutation[0]], axis=0)
        length = calculate_len(permutation)
        results.append(length)

        if length < best_len:
            best_len = length
            best = permutation


    g1 = []
    g2 = []

    print(f"Groups of {size1}", file=outfile)

    for i in range(0, permutation_no, size1):
        g1.append(min(results[i:i+size1]))

    print(sum(g1) / len(g1), file=outfile)

    print(f"Groups of {size2}", file=outfile)

    for i in range(0, permutation_no, size2):
        g2.append(min(results[i:i+size2]))

    print(sum(g2) / len(g2), file=outfile)

    print("The best one", file=outfile)

    print(min(results), file=outfile)

    plot_solution(best, sys.argv[1])

    