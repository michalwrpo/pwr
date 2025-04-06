import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, avgN: List[int], avgC: List[float], avgS: List[float], title: str, subtitle: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=(0.95*min(avgS)), top=(1.05*max(avgC)))
    plt.plot(avgN, avgC, c='r', label="Comparisons")
    plt.plot(avgN, avgS, c='b', label="Swaps")
    plt.xlabel("k")
    plt.ylabel('Average value')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

if __name__ == "__main__":
    data = open("hybrid.txt").read().strip().split("\n")
    for i in range(len(data)):
        data[i] = list(map(int, data[i].split(" ")))

    k = []
    avgcomps = []
    avgswaps = []

    for triple in data:
        if triple[0] not in k:
            k.append(triple[0])
            if triple[0] != k[0]:
                avgcomps.append(sumc/r)
                avgswaps.append(sums/r)
            sumc = 0
            sums = 0
            r = 0

        sumc += triple[1]
        sums += triple[2]
        r += 1

    avgcomps.append(sumc/r)
    avgswaps.append(sums/r)

    print("Min comparisons for k = ", k[avgcomps.index(min(avgcomps))], "\nMin swaps for k = ", k[avgswaps.index(min(avgswaps))])

    makegraph("hybrid.png", k, avgcomps, avgswaps, "Quick-Insertion hybrid sort", "for $n=10000$")
    

