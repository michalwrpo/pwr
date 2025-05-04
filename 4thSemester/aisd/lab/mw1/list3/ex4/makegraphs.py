import matplotlib.pyplot as plt
import numpy
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], A: List[float], B: List[float], C: List[float], D: List[float], E: List[float], aname: str, bname: str, cname: str, dname: str, ename: str, title: str, subtitle: str, log: bool) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=(0.95*min(A + B + C + D + E)), top=(1.05*max(A + B + C + D + E)))
    plt.plot(n, A, c='r', label=aname)
    plt.plot(n, B, c='g', label=bname)
    plt.plot(n, C, c='b', label=cname)
    plt.plot(n, D, c='y', label=dname)
    plt.plot(n, E, c='m', label=ename)
    if log:
        plt.plot(n, numpy.log2(n), c='b', linestyle='dashed', label="$log_2(n)$")
    plt.xlabel("n")
    plt.ylabel('Average value')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

def divlists(x: List[float], y: List[float]) -> List[float]:
    ans = []
    if (len(x) == len(y)):
        for i in range(len(x)):
            ans.append(x[i]/y[i])
    return ans

if __name__ == "__main__":
    data = open("data.txt").read().strip().split("\n")
        
    low = []
    mid = []
    high = []
    outside = []
    rand = []

    n = list(map(int, data[0].split()))
    for i in range(2):
        low.append(list(map(float, data[1 + i].split())))
        mid.append(list(map(float, data[3 + i].split())))
        high.append(list(map(float, data[5 + i].split())))
        outside.append(list(map(float, data[7 + i].split())))
        rand.append(list(map(float, data[9 + i].split())))

    logs = numpy.log2(n)
    lowdiff, middiff, highdiff, outdiff, randdiff, = 0, 0, 0, 0, 0
    for i in range(len(n)):
        lowdiff += low[0][i] - logs[i]
        middiff += mid[0][i] - logs[i]
        highdiff += high[0][i] - logs[i]
        outdiff += outside[0][i] - logs[i]
        randdiff += rand[0][i] - logs[i]

    lowdiff /= len(n)
    middiff /= len(n)
    highdiff /= len(n)
    outdiff /= len(n)
    randdiff /= len(n)

    makegraph(
        "binsearch_comps.png", 
        n, 
        low[0], 
        mid[0],
        high[0],
        outside[0],
        rand[0],
        "Values around start, $c =$" + str(round(lowdiff, 2)),
        "Values around middle, $c = $" + str(round(middiff, 2)),
        "Values around end, $c =$" + str(round(highdiff, 2)),
        "Values outside the array, $c =$" + str(round(outdiff, 2)),
        "Random values, $c =$" + str(round(randdiff, 2)),
        "Comparisons for Binary Search",
        "$n \\in \\{1000, 2000, ..., 100000\\}$",
        True
    )

    lowdiff, middiff, highdiff, outdiff, randdiff, = 0, 0, 0, 0, 0
    for i in range(len(n)):
        lowdiff += low[1][i] - logs[i]
        middiff += mid[1][i] - logs[i]
        highdiff += high[1][i] - logs[i]
        outdiff += outside[1][i] - logs[i]
        randdiff += rand[1][i] - logs[i]

    lowdiff /= len(n)
    middiff /= len(n)
    highdiff /= len(n)
    outdiff /= len(n)
    randdiff /= len(n)


    makegraph(
        "binsearch_time.png", 
        n, 
        low[1], 
        mid[1],
        high[1],
        outside[1],
        rand[1],
        "Values around start, $c =$" + str(round(lowdiff, 2)),
        "Values around middle, $c = $" + str(round(middiff, 2)),
        "Values around end, $c =$" + str(round(highdiff, 2)),
        "Values outside the array, $c =$" + str(round(outdiff, 2)),
        "Random values, $c =$" + str(round(randdiff, 2)),
        "Time of Binary Search [ns]",
        "$n \\in \\{1000, 2000, ..., 100000\\}$",
        False
    )