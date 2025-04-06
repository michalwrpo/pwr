import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], A: List[float], B: List[float], C: List[float], D: List[float], E: List[float], aname: str, bname: str, cname: str, dname: str, ename: str, title: str, subtitle: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=(0.95*min(B)), top=(1.05*max(A)))
    plt.plot(n, A, c='r', label=aname)
    plt.plot(n, B, c='g', label=bname)
    plt.plot(n, C, c='b', label=cname)
    plt.plot(n, D, c='y', label=dname)
    plt.plot(n, E, c='m', label=ename)
    plt.xlabel("n")
    plt.ylabel('Average value')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

if __name__ == "__main__":
    data = open("data.txt").read().strip().split("\n")
    msdata = open("../ex3/msdata.txt").read().strip().split("\n")
        
    insort = []
    quick = []
    hybrid = []
    mine = []
    dpqs = []
    merge = []

    n = list(map(int, data[0].split()))
    for i in range(6):
        insort.append(list(map(float, data[1 + i].split())))
        quick.append(list(map(float, data[7 + i].split())))
        hybrid.append(list(map(float, data[13 + i].split())))
        mine.append(list(map(float, data[19 + i].split())))
        dpqs.append(list(map(float, data[25 + i].split())))

    nl = list(map(int, data[31].split()))
    for i in range(6):
        quick.append(list(map(float, data[32 + i].split())))
        hybrid.append(list(map(float, data[38 + i].split())))
        mine.append(list(map(float, data[44 + i].split())))
        dpqs.append(list(map(float, data[50 + i].split())))
        merge.append(list(map(float, msdata[i].split())))
        

    makegraph(
        "c_small_n_k1.png", 
        n, 
        insort[0], 
        quick[0],
        hybrid[0],
        mine[0],
        dpqs[0],
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons for small values of $n$",
        "$k=1$"
    )

    makegraph(
        "s_small_n_k1.png", 
        n, 
        insort[1], 
        quick[1],
        hybrid[1],
        mine[1],
        dpqs[1],
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps for small values of $n$",
        "$k=1$"
    )

    makegraph(
        "c_small_n_k2.png", 
        n, 
        insort[2], 
        quick[2],
        hybrid[2],
        mine[2],
        dpqs[2],
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons for small values of $n$",
        "$k=10$"
    )

    makegraph(
        "s_small_n_k2.png", 
        n, 
        insort[3], 
        quick[3],
        hybrid[3],
        mine[3],
        dpqs[3],
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps for small values of $n$",
        "$k=10$"
    )

    makegraph(
        "c_small_n_k3.png", 
        n, 
        insort[4], 
        quick[4],
        hybrid[4],
        mine[4],
        dpqs[4],
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons for small values of $n$",
        "$k=100$"
    )

    makegraph(
        "s_small_n_k3.png", 
        n, 
        insort[5], 
        quick[5],
        hybrid[5],
        mine[5],
        dpqs[5],
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps for small values of $n$",
        "$k=100$"
    )

    # big n

    makegraph(
        "c_big_n_k1.png", 
        nl, 
        merge[0], 
        quick[6],
        hybrid[6],
        mine[6],
        dpqs[6],
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons for big values of $n$",
        "$k=1$"
    )

    makegraph(
        "s_big_n_k1.png", 
        nl, 
        merge[1], 
        quick[7],
        hybrid[7],
        mine[7],
        dpqs[7],
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps for big values of $n$",
        "$k=1$"
    )

    makegraph(
        "c_big_n_k2.png", 
        nl, 
        merge[2], 
        quick[8],
        hybrid[8],
        mine[8],
        dpqs[8],
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons for big values of $n$",
        "$k=10$"
    )

    makegraph(
        "s_big_n_k2.png", 
        nl, 
        merge[3], 
        quick[9],
        hybrid[9],
        mine[9],
        dpqs[9],
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps for big values of $n$",
        "$k=10$"
    )

    makegraph(
        "c_big_n_k3.png", 
        nl, 
        merge[4], 
        quick[10],
        hybrid[10],
        mine[10],
        dpqs[10],
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons for big values of $n$",
        "$k=100$"
    )

    makegraph(
        "s_big_n_k3.png", 
        nl, 
        merge[5], 
        quick[11],
        hybrid[11],
        mine[11],
        dpqs[11],
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps for big values of $n$",
        "$k=100$"
    )

