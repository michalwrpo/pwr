import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], A: List[float], B: List[float], C: List[float], D: List[float], E: List[float], F: List[float], aname: str, bname: str, cname: str, dname: str, ename: str, fname: str, title: str, subtitle: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=(0.95*min(A + B + C + D + E + F)), top=(1.05*max(A + B + C + D + E + F)))
    plt.plot(n, A, c='r', label=aname)
    plt.plot(n, B, c='g', label=bname)
    plt.plot(n, C, c='b', label=cname)
    plt.plot(n, D, c='y', label=dname)
    plt.plot(n, E, c='m', label=ename)
    plt.plot(n, F, c='black', label=fname)
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
        
    rsel = []
    sel = []

    n = list(map(int, data[0].split()))
    for i in range(6):
        rsel.append(list(map(float, data[1 + i].split())))
        sel.append(list(map(float, data[7 + i].split())))

    makegraph(
        "selects_comps.png", 
        n, 
        rsel[0], 
        rsel[2],
        rsel[4],
        sel[0],
        sel[2],
        sel[4],
        "Random select, $k = \\frac{1}{20}n$",
        "Random select, $k = \\frac{1}{2}n$",
        "Random select, $k = \\frac{3}{4}n$",
        "Select, $k = \\frac{1}{20}n$",
        "Select, $k = \\frac{1}{2}n$",
        "Select, $k = \\frac{3}{4}n$",
        "Comparisons for Select and Random Select",
        "$n \\in \\{100, 200, ..., 50000\\}$"
    )

    makegraph(
        "selects_swaps.png", 
        n, 
        rsel[1], 
        rsel[3],
        rsel[5],
        sel[1],
        sel[3],
        sel[5],
        "Random select, $k = \\frac{1}{20}n$",
        "Random select, $k = \\frac{1}{2}n$",
        "Random select, $k = \\frac{3}{4}n$",
        "Select, $k = \\frac{1}{20}n$",
        "Select, $k = \\frac{1}{2}n$",
        "Select, $k = \\frac{3}{4}n$",
        "Swaps for Select and Random Select",
        "$n \\in \\{100, 200, ..., 50000\\}$"
    )
