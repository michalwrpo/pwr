import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], y: List[List[float]], names: List[str], title: str, subtitle: str, log: bool) -> None:
    y_max, y_min = y[0][0], y[0][0]
    for values in y:
        for val in values:
            if val > y_max:
                y_max = val
            elif val < y_min:
                y_min = val

    if len(y) != len(names):
        raise IndexError("Length of y and names don't match")
             
    colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    if log:
        plt.ylim(bottom=1, top=(1.05*y_max))
    else:
        plt.ylim(bottom=(0.95*y_min), top=(1.05*y_max))
    for i in range(len(y)):
        plt.plot(n, y[i], c=colors[i % 7], label=names[i])
    plt.xlabel("n")
    plt.ylabel('Average value')

    if log:
        plt.yscale('log')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

def makegraphscatter(fileName: str, n: List[List[int]], y: List[List[float]], names: List[str], title: str, subtitle: str, log = False, colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']) -> None:
    y_max, y_min = y[0][0], y[0][0]
    for values in y:
        for val in values:
            if val > y_max:
                y_max = val
            elif val < y_min:
                y_min = val

    if len(y) != len(names):
        raise IndexError("Length of y and names don't match")
             
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    if log:
        plt.ylim(bottom=1, top=(1.05*y_max))
    else:
        plt.ylim(bottom=(0.95*y_min), top=(1.05*y_max))
    for i in range(len(y)):
        if names[i] != "":
            plt.scatter(n[i], y[i], s=2, c=colors[i % len(colors)], label=names[i])
        else:
            plt.scatter(n[i], y[i], s=2, c=colors[i % len(colors)])
    plt.xlabel("n")
    plt.ylabel('Average value')

    if log:
        plt.yscale('log')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

if __name__ == "__main__":
    data = open("experiment.txt").read().strip().split("\n")

    make = [[0] for _ in range(10)]
    n_make = [1]

    h1 = [[0 for _ in range(500)] for _ in range(5)]
    n_h1 = [i for i in range(2, 502)]

    h2 = [[0 for _ in range(500)] for _ in range(5)]
    n_h2 = [i for i in range(502, 1002)]
    
    union = [[] for _ in range(5)]
    n_union = [1002]

    extr = [[0 for _ in range(1000)] for _ in range(5)]
    n_extr = [i for i in range(1003, 2003)]

    result = []

    for line in data:
        line = line.split(" ")
        k = int(line[0])

        if line[2] == "Union":
            union[k] = [int(line[3])]
            continue

        i = int(line[3])
        if line[1] == "H1":
            h1[k][i] = int(line[4])
        elif line[1] == "H2":
            h2[k][i] = int(line[4])
        elif line[2] == "Extract":
            extr[k][i] = int(line[4])

    print

    n = [n_make, n_h1, n_h2, n_union, n_extr]
    names = ["Make-Heap", "$H_1$ Heap-Insert", "$H_2$ Heap-Insert", "Heap-Union", "Extract-Min"]

    for i in range(5):
        results = [make[i], h1[i], h2[i], union[i], extr[i]]
        makegraphscatter("experiment" + str(i) + ".png", n, results, names, "Binomial Heap", "Comparisons per operation, attempt " + str(i))

    data = open("data.txt").read().strip().split("\n")

    n = [100 * i for i in range(1, 101)]

    ans = [[0] * 100]

    for line in data:
        line = line.split(" ")
        i = int(line[0]) // 100 - 1
        ans[0][i] += int(line[1])

    for i in range(len(ans[0])):
        ans[0][i] /= n[i]
        ans[0][i] /= 10

    makegraph("comparisons.png", n, ans, ["Average comparisons"], "Binomial Heap", "Average comparisons per n", False)
