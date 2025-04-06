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
    plt.ylim(bottom=(0.95*min(A + B + C + D + E)), top=(1.05*max(A + B + C + D + E)))
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

def divlists(x: List[float], y: List[float]) -> List[float]:
    ans = []
    if (len(x) == len(y)):
        for i in range(len(x)):
            ans.append(x[i]/y[i])
    return ans

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
        
    # small n
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

    # divided by n

    # small n
    makegraph(
        "cn_small_n_k1.png", 
        n, 
        divlists(insort[0], n), 
        divlists(quick[0], n),
        divlists(hybrid[0], n),
        divlists(mine[0], n),
        divlists(dpqs[0], n),
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons / $n$ for small values of $n$",
        "$k=1$"
    )

    makegraph(
        "sn_small_n_k1.png", 
        n, 
        divlists(insort[1], n), 
        divlists(quick[1], n),
        divlists(hybrid[1], n),
        divlists(mine[1], n),
        divlists(dpqs[1], n),
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps / $n$ for small values of $n$",
        "$k=1$"
    )

    makegraph(
        "cn_small_n_k2.png", 
        n, 
        divlists(insort[2], n), 
        divlists(quick[2], n),
        divlists(hybrid[2], n),
        divlists(mine[2], n),
        divlists(dpqs[2], n),
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons / $n$ for small values of $n$",
        "$k=10$"
    )

    makegraph(
        "sn_small_n_k2.png", 
        n, 
        divlists(insort[3], n), 
        divlists(quick[3], n),
        divlists(hybrid[3], n),
        divlists(mine[3], n),
        divlists(dpqs[3], n),
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps / $n$ for small values of $n$",
        "$k=10$"
    )

    makegraph(
        "cn_small_n_k3.png", 
        n, 
        divlists(insort[4], n), 
        divlists(quick[4], n),
        divlists(hybrid[4], n),
        divlists(mine[4], n),
        divlists(dpqs[4], n),
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons / $n$ for small values of $n$",
        "$k=100$"
    )

    makegraph(
        "sn_small_n_k3.png", 
        n, 
        divlists(insort[5], n), 
        divlists(quick[5], n),
        divlists(hybrid[5], n),
        divlists(mine[5], n),
        divlists(dpqs[5], n),
        "Insertion Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps / $n$ for small values of $n$",
        "$k=100$"
    )

    # big n

    makegraph(
        "cn_big_n_k1.png", 
        nl, 
        divlists(merge[0], nl),
        divlists(quick[6], nl),
        divlists(hybrid[6], nl),
        divlists(mine[6], nl),
        divlists(dpqs[6], nl),
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons / $n$ for big values of $n$",
        "$k=1$"
    )

    makegraph(
        "sn_big_n_k1.png", 
        nl, 
        divlists(merge[1], nl),
        divlists(quick[7], nl),
        divlists(hybrid[7], nl),
        divlists(mine[7], nl),
        divlists(dpqs[7], nl),
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps / $n$ for big values of $n$",
        "$k=1$"
    )

    makegraph(
        "cn_big_n_k2.png", 
        nl, 
        divlists(merge[2], nl), 
        divlists(quick[8], nl),
        divlists(hybrid[8], nl),
        divlists(mine[8], nl),
        divlists(dpqs[8], nl),
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons / $n$ for big values of $n$",
        "$k=10$"
    )

    makegraph(
        "sn_big_n_k2.png", 
        nl, 
        divlists(merge[3], nl), 
        divlists(quick[9], nl),
        divlists(hybrid[9], nl),
        divlists(mine[9], nl),
        divlists(dpqs[9], nl),
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps / $n$ for big values of $n$",
        "$k=10$"
    )

    makegraph(
        "cn_big_n_k3.png", 
        nl, 
        divlists(merge[4], nl), 
        divlists(quick[10], nl),
        divlists(hybrid[10], nl),
        divlists(mine[10], nl),
        divlists(dpqs[10], nl),
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Comparisons / $n$ for big values of $n$",
        "$k=100$"
    )

    makegraph(
        "sn_big_n_k3.png", 
        nl, 
        divlists(merge[5], nl), 
        divlists(quick[11], nl),
        divlists(hybrid[11], nl),
        divlists(mine[11], nl),
        divlists(dpqs[11], nl),
        "Merge Sort",
        "Quicksort",
        "Hybrid Sort",
        "Mine Sort",
        "Dual-Pivot Quick Sort",
        "Swaps / $n$ for big values of $n$",
        "$k=100$"
    )