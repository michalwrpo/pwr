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
    data = open("data.txt").read().strip().split("\n")
        