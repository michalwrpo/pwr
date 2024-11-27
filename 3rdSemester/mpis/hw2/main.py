import numpy as np
import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], y: List[float], avgN: List[int], avgY: List[float], title: str, subtitle: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=0, top=(1.05*max(y)))
    plt.scatter(n, y, c='b', s=1, label="Approximated values")
    plt.scatter(avgN, avgY, c='r', s=8, label="Mean approximated value")
    plt.ticklabel_format(axis='y', style='scientific', scilimits=[-5, 5], useMathText=True)
    plt.xlabel("Number of balls")
    plt.ylabel('Approximated value')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

def makegraph_simple(fileName: str, n: List[int], y: List[float], title: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=0, top=(1.05*max(y)))
    plt.scatter(n, y, c='b', s=8, label="Approximated values")
    plt.xlabel("n")
    plt.ylabel('Value')
    plt.suptitle(title, fontsize=20)
    plt.legend()
    plt.savefig(fileName)

if __name__ == "__main__":
    data = open("results.txt").read().strip().split("\n")
    for i in range(len(data)):
        data[i] = data[i].split(" ")
        data[i].append(int(data[i][5]) - int(data[i][4]))

    averageData = []

    nCount = 100
    k = 50

    for i in range(nCount):
        sumB, sumU, sumC, sumD, sumDC = 0, 0, 0, 0, 0
        for j in range(k):
            sumB += int(data[k*i + j][2])
            sumU += int(data[k*i + j][3])
            sumC += int(data[k*i + j][4])
            sumD += int(data[k*i + j][5])
            sumDC += int(data[k*i + j][6])
        averageData.append([data[k*i][0], sumB/k, sumU/k, sumC/k, sumD/k, sumDC/k])

    n, B, U, C, D, DC = [], [], [], [], [], []
    avgN, avgB, avgU, avgC, avgD, avgDC = [], [], [], [], [], []

    for line in data:
        n.append(int(line[0]))
        B.append(int(line[2]))
        U.append(int(line[3]))
        C.append(int(line[4]))
        D.append(int(line[5]))
        DC.append(int(line[6]))

    for line in averageData:
        avgN.append(int(line[0]))
        avgB.append(int(line[1]))
        avgU.append(int(line[2]))
        avgC.append(int(line[3]))
        avgD.append(int(line[4]))
        avgDC.append(int(line[5]))

    b1 = [ (avgB[ i // 1000 - 1] / i) for i in avgN ]
    b2 = [ (avgB[ i // 1000 - 1] / np.sqrt(i)) for i in avgN ]
    u1 = [ (avgU[ i // 1000 - 1] / i) for i in avgN ]
    c1 = [ (avgC[ i // 1000 - 1] / i) for i in avgN ]
    c2 = [ (avgC[ i // 1000 - 1] / ( i * np.log(i) )) for i in avgN ]
    c3 = [ (avgC[ i // 1000 - 1] / (i**i)) for i in avgN ]
    d1 = [ (avgD[ i // 1000 - 1] / i) for i in avgN ]
    d2 = [ (avgD[ i // 1000 - 1] / ( i * np.log(i) )) for i in avgN ]
    d3 = [ (avgD[ i // 1000 - 1] / (i**i)) for i in avgN ]
    dc1 = [ (avgDC[ i // 1000 - 1] / i) for i in avgN ]
    dc2 = [ (avgDC[ i // 1000 - 1] / ( i * np.log(i) )) for i in avgN ]
    dc3 = [ (avgDC[ i // 1000 - 1] / ( i * np.log(np.log(i)) )) for i in avgN ]

    makegraph("Bn.png", n, B, avgN, avgB, "$B_n$", "50 repetitions")
    makegraph("Un.png", n, U, avgN, avgU, "$U_n$", "50 repetitions")
    makegraph("Cn.png", n, C, avgN, avgC, "$C_n$", "50 repetitions")
    makegraph("Dn.png", n, D, avgN, avgD, "$D_n$", "50 repetitions")
    makegraph("DCn.png", n, DC, avgN, avgDC, "$D_n - C_n$", "50 repetitions")

    makegraph_simple("b1.png", avgN, b1, "$\\frac{b(n)}{n}$")
    makegraph_simple("b2.png", avgN, b2, "$\\frac{b(n)}{\\sqrt{n}}$")
    makegraph_simple("u1.png", avgN, u1, "$\\frac{u(n)}{n}$")
    makegraph_simple("c1.png", avgN, c1, "$\\frac{c(n)}{n}$")
    makegraph_simple("c2.png", avgN, c2, "$\\frac{c(n)}{n \\ln{n}}$")
    makegraph_simple("c3.png", avgN, c3, "$\\frac{c(n)}{n^2}$")
    makegraph_simple("d1.png", avgN, d1, "$\\frac{d(n)}{n}$")
    makegraph_simple("d2.png", avgN, d2, "$\\frac{d(n)}{n \\ln{n}}$")
    makegraph_simple("d3.png", avgN, d3, "$\\frac{d(n)}{n^2}$")
    makegraph_simple("dc1.png", avgN, dc1, "$\\frac{d(n) - c(n)}{n}$")
    makegraph_simple("dc2.png", avgN, dc2, "$\\frac{d(n) - c(n)}{n \\ln{n}}$")
    makegraph_simple("dc3.png", avgN, dc3, "$\\frac{d(n) - c(n)}{n \\ln{\\ln{n}}}$")
