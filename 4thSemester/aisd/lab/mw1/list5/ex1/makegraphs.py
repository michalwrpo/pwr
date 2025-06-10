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

    print(y_max)

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

if __name__ == "__main__":
    data = open("out.txt").read().strip().split("\n")

    prim = []
    kruskal = []

    for line in data:
        line = line.split(" ")
        if line[0] == "Prim":
            prim.append(list(map(float, line[1:])))
        else:
            kruskal.append(list(map(float, line[1:])))

    results = [prim, kruskal]
    ans = []

    n = [1000*x for x in range(1, 26)]

    for k in range(len(results)):
        avg = [0 for _ in range(25)]
        for result in results[k]:
            ind = int(result[0]) // 1000 - 1
            avg[ind] += result[1] * 1000 # miliseconds
        for j in range(25):
            avg[j] = avg[j] / 10 
        if k == 0:
            ans.append(avg)
        else:
            ans.append(avg)
            
    print(ans)

makegraph("mst.png", n, ans, ["Prim's algorithm", "Kruskal's algorithm"], "MST", "Time spent [ms]", True)
