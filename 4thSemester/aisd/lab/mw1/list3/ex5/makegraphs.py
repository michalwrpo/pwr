import matplotlib.pyplot as plt
import numpy as np
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], A: List[float], B: List[float], C: List[float], D: List[float], aname: str, bname: str, cname: str, dname: str, title: str, subtitle: str, n2: bool) -> None:
    nlog = [x * np.log2(x) for x in n]
    nsquared = [x ** 2 for x in n]

    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=(0.95*min(A + B + C + D)), top=(1.05*max(A + B + C + D)))
    plt.plot(n, A, c='r', label=aname)
    plt.plot(n, B, c='g', label=bname)
    plt.plot(n, C, c='b', label=cname)
    plt.plot(n, D, c='y', label=dname)
    plt.plot(n, nlog, c='black', linestyle='dashed', label='$n \\cdot \\log_2(n)$')
    if n2:
        plt.plot(n, nsquared, c='gray', linestyle='dashed', label='$n^2$')

    plt.yscale('log')
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
        
    quick = []
    dpqs = []
    squick = []
    sdpqs = []

    n = list(map(int, data[0].split()))
    for i in range(4):
        quick.append(list(map(float, data[1 + i].split())))
        dpqs.append(list(map(float, data[5 + i].split())))
        squick.append(list(map(float, data[9 + i].split())))
        sdpqs.append(list(map(float, data[13 + i].split())))


    nlog = [x * np.log2(x) for x in n]
    nsquared = [x ** 2 for x in n]

    qcoff = 0
    dcoff = 0
    sqcoff = 0
    sdcoff = 0
    for i in range(len(n)):
        qcoff += quick[0][i] / nlog[i]
        dcoff += dpqs[0][i] / nlog[i]
        sqcoff += squick[0][i] / nlog[i]
        sdcoff += sdpqs[0][i] / nlog[i]

    qcoff /= len(n)
    dcoff /= len(n)
    sqcoff /= len(n)
    sdcoff /= len(n)
        
    makegraph(
        "comps_avg.png", 
        n, 
        quick[0],
        dpqs[0],
        squick[0],
        sdpqs[0],
        "Quicksort, $c =$" + str(round(qcoff, 2)),
        "Dual-Pivot Quick Sort, $c =$" + str(round(dcoff, 2)),
        "Quicksort with Select, $c =$" + str(round(sqcoff, 2)),
        "DPQS with Select, $c =$" + str(round(sdcoff, 2)),
        "Comparisons for variants of Quicksort (Average case)",
        "$n \\in \\{100, 200, ..., 10000\\}$",
        False
    )

    qcoff = 0
    dcoff = 0
    sqcoff = 0
    sdcoff = 0
    for i in range(len(n)):
        qcoff += quick[1][i] / nlog[i]
        dcoff += dpqs[1][i] / nlog[i]
        sqcoff += squick[1][i] / nlog[i]
        sdcoff += sdpqs[1][i] / nlog[i]

    qcoff /= len(n)
    dcoff /= len(n)
    sqcoff /= len(n)
    sdcoff /= len(n)

    makegraph(
        "time_avg.png", 
        n, 
        quick[1],
        dpqs[1],
        squick[1],
        sdpqs[1],
        "Quicksort, $c =$" + str(round(qcoff, 2)),
        "Dual-Pivot Quick Sort, $c =$" + str(round(dcoff, 2)),
        "Quicksort with Select, $c =$" + str(round(sqcoff, 2)),
        "DPQS with Select, $c =$" + str(round(sdcoff, 2)),
        "Time of variants of Quicksort (Average case)",
        "$n \\in \\{100, 200, ..., 10000\\}$",
        False
    )

    qcoff = 0
    dcoff = 0
    sqcoff = 0
    sdcoff = 0
    for i in range(len(n)):
        qcoff += quick[2][i] / nsquared[i]
        dcoff += dpqs[2][i] / nsquared[i]
        sqcoff += squick[2][i] / nlog[i]
        sdcoff += sdpqs[2][i] / nlog[i]

    qcoff /= len(n)
    dcoff /= len(n)
    sqcoff /= len(n)
    sdcoff /= len(n)

    makegraph(
        "comps_worst.png", 
        n, 
        quick[2],
        dpqs[2],
        squick[2],
        sdpqs[2],
        "Quicksort, $c =$" + str(round(qcoff, 2)),
        "Dual-Pivot Quick Sort, $c =$" + str(round(dcoff, 2)),
        "Quicksort with Select, $c =$" + str(round(sqcoff, 2)),
        "DPQS with Select, $c =$" + str(round(sdcoff, 2)),
        "Comparisons for variants of Quicksort (Worst case)",
        "$n \\in \\{100, 200, ..., 10000\\}$",
        True
    )

    qcoff = 0
    dcoff = 0
    sqcoff = 0
    sdcoff = 0
    for i in range(len(n)):
        qcoff += quick[3][i] / nsquared[i]
        dcoff += dpqs[3][i] / nsquared[i]
        sqcoff += squick[3][i] / nlog[i]
        sdcoff += sdpqs[3][i] / nlog[i]

    qcoff /= len(n)
    dcoff /= len(n)
    sqcoff /= len(n)
    sdcoff /= len(n)


    makegraph(
        "time_worst.png", 
        n, 
        quick[3],
        dpqs[3],
        squick[3],
        sdpqs[3],
        "Quicksort, $c =$" + str(round(qcoff, 2)),
        "Dual-Pivot Quick Sort, $c =$" + str(round(dcoff, 2)),
        "Quicksort with Select, $c =$" + str(round(sqcoff, 2)),
        "DPQS with Select, $c =$" + str(round(sdcoff, 2)),
        "Time of variants of Quicksort (Worst case)",
        "$n \\in \\{100, 200, ..., 10000\\}$",
        True
    )