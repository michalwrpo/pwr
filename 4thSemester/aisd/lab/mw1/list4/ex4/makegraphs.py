import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], y: List[List[float]], names: List[str], title: str, subtitle: str) -> None:
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
    plt.ylim(bottom=(0.95*y_min), top=(1.05*y_max))
    for i in range(len(y)):
        plt.plot(n, y[i], c=colors[i % 7], label=names[i])
    plt.xlabel("n")
    plt.ylabel('Average value')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

if __name__ == "__main__":
    data = open("out.txt").read().strip().split("\n")

    rand_in = []
    rand_del = []
    asc_in = []
    asc_del = []

    for line in data:
        line = line.split(" ")
        if line[0] == "rand":
            if line[1] == "insert":
                rand_in.append(list(map(int, line[2:])))
            else:
                rand_del.append(list(map(int, line[2:])))
        else:
            if line[1] == "insert":
                asc_in.append(list(map(int, line[2:])))
            else:
                asc_del.append(list(map(int, line[2:])))

    results = [rand_in, rand_del, asc_in, asc_del]

    avg = []
    maxes = []
    for _ in range(10):
        avg.append(0)
        maxes.append(0)

    r_c = []
    r_r = []
    r_w = []
    r_h = []
    a_c = []
    a_r = []
    a_w = []
    a_h = []

    n = [10000*x for x in range(1, 11)]

    for k in range(len(results)):
        for i in range(4):
            for j in range(10):
                avg[j] = 0
                maxes[j] = 0
            for result in results[k]:
                ind = result[0] // 10000 - 1
                avg[ind] += result[2*i + 1]
                if result[2*i + 2] > maxes[ind]:
                    maxes[ind] = result[2*i + 2]
            for j in range(10):
                avg[j] = avg[j] / 20
            if k < 2:
                if i == 0:
                    r_c.append(avg.copy())
                    r_c.append(maxes.copy())
                if i == 1:
                    r_r.append(avg.copy())
                    r_r.append(maxes.copy())
                if i == 2:
                    r_w.append(avg.copy())
                    r_w.append(maxes.copy())
                if i == 3:
                    r_h.append(avg.copy())
                    r_h.append(maxes.copy())
            else:
                if i == 0:
                    a_c.append(avg.copy())
                    a_c.append(maxes.copy())
                if i == 1:
                    a_r.append(avg.copy())
                    a_r.append(maxes.copy())
                if i == 2:
                    a_w.append(avg.copy())
                    a_w.append(maxes.copy())
                if i == 3:
                    a_h.append(avg.copy())
                    a_h.append(maxes.copy())

makegraph("random_comp.png", n, r_c, ["insert average", "insert max", "delete average", "delete max"], "Comparisons", "for random inserts")
makegraph("random_reads.png", n, r_r, ["insert average", "insert max", "delete average", "delete max"], "Reads", "for random inserts")
makegraph("random_writes.png", n, r_w, ["insert average", "insert max", "delete average", "delete max"], "Writes", "for random inserts")
makegraph("random_height.png", n, r_h, ["insert average", "insert max", "delete average", "delete max"], "Height", "for random inserts")

makegraph("ascending_comp.png", n, a_c, ["insert average", "insert max", "delete average", "delete max"], "Comparisons", "for ascending inserts")
makegraph("ascending_reads.png", n, a_r, ["insert average", "insert max", "delete average", "delete max"], "Reads", "for ascending inserts")
makegraph("ascending_writes.png", n, a_w, ["insert average", "insert max", "delete average", "delete max"], "Writes", "for ascending inserts")
makegraph("ascending_height.png", n, a_h, ["insert average", "insert max", "delete average", "delete max"], "Height", "for ascending inserts")
