import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], A: List[float], B: List[float], C: List[float], D: List[float], aname: str, bname: str, cname: str, dname: str, title: str, subtitle: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=(0.95*min(A + B + C + D)), top=(1.05*max(A + B + C + D)))
    plt.plot(n, A, c='r', label=aname)
    plt.plot(n, B, c='g', label=bname)
    plt.plot(n, C, c='b', label=cname)
    plt.plot(n, D, c='y', label=dname)
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
        
    sel3 = []
    sel5 = []
    sel7 = []
    sel9 = []

    n = list(map(int, data[0].split()))
    for i in range(6):
        sel3.append(list(map(float, data[1 + i].split())))
        sel5.append(list(map(float, data[7 + i].split())))
        sel7.append(list(map(float, data[13 + i].split())))
        sel9.append(list(map(float, data[19 + i].split())))


    makegraph(
        "selects_comps1.png", 
        n, 
        sel3[0], 
        sel5[0],
        sel7[0],
        sel9[0],
        "Select, $3 groups$",
        "Select, $5 groups$",
        "Select, $7 groups$",
        "Select, $9 groups$",
        "Comparisons for Select",
        "$n \\in \\{100, 200, ..., 50000\\}$, $k = 1$"
    )

    makegraph(
        "selects_swaps1.png", 
        n, 
        sel3[1], 
        sel5[1],
        sel7[1],
        sel9[1],
        "Select, $3 groups$",
        "Select, $5 groups$",
        "Select, $7 groups$",
        "Select, $9 groups$",
        "Swaps for Select",
        "$n \\in \\{100, 200, ..., 50000\\}$, $k = 1$"
    )

    makegraph(
        "selects_comps2.png", 
        n, 
        sel3[2], 
        sel5[2],
        sel7[2],
        sel9[2],
        "Select, $3 groups$",
        "Select, $5 groups$",
        "Select, $7 groups$",
        "Select, $9 groups$",
        "Comparisons for Select",
        "$n \\in \\{100, 200, ..., 50000\\}$, $k = \\frac{1}{2}n$"
    )

    makegraph(
        "selects_swaps2.png", 
        n, 
        sel3[3], 
        sel5[3],
        sel7[3],
        sel9[3],
        "Select, $3 groups$",
        "Select, $5 groups$",
        "Select, $7 groups$",
        "Select, $9 groups$",
        "Swaps for Select",
        "$n \\in \\{100, 200, ..., 50000\\}$, $k = \\frac{1}{2}n$"
    )

    makegraph(
        "selects_comps3.png", 
        n, 
        sel3[4], 
        sel5[4],
        sel7[4],
        sel9[4],
        "Select, $3 groups$",
        "Select, $5 groups$",
        "Select, $7 groups$",
        "Select, $9 groups$",
        "Comparisons for Select",
        "$n \\in \\{100, 200, ..., 50000\\}$, $k = \\frac{3}{4}n$"
    )

    makegraph(
        "selects_swaps3.png", 
        n, 
        sel3[5], 
        sel5[5],
        sel7[5],
        sel9[5],
        "Select, $3 groups$",
        "Select, $5 groups$",
        "Select, $7 groups$",
        "Select, $9 groups$",
        "Swaps for Select",
        "$n \\in \\{100, 200, ..., 50000\\}$, $k = \\frac{3}{4}n$"
    )