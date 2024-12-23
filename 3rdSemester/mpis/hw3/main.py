import numpy as np
import matplotlib.pyplot as plt
from typing import List

plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})

def makegraph(fileName: str, n: List[int], y: List[float], avgN: List[int], avgY: List[float], title: str, subtitle: str, x_axis: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.margins(0, 0)
    plt.ylim(bottom=0, top=(1.05*max(y)))
    plt.scatter(n, y, c='b', s=1, label="Simulated values")
    plt.scatter(avgN, avgY, c='r', s=8, label="Mean values")
    plt.ticklabel_format(axis='y', style='scientific', scilimits=[-5, 5], useMathText=True)
    plt.xlabel(x_axis)
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
    plt.scatter(n, y, c='b', s=8, label="Mean values")
    plt.xlabel("n")
    plt.ylabel('Value')
    plt.suptitle(title, fontsize=20)
    plt.legend()
    plt.savefig(fileName)

if __name__ == "__main__":
    data1a = open("1a.txt").read().strip().split("\n")
    data1b = open("1b.txt").read().strip().split("\n")

    # ex. 1

    k = 50
    repetitions = 100
    x = []
    avgX = []
    L1, L2 = [], []
    avgL1, avgL2 = [], []

    for i in range(len(data1a)):
        data1a[i] = data1a[i].split(" ")
        data1b[i] = data1b[i].split(" ")

        x.append(int(data1a[i][0]))
        L1.append(int(data1a[i][2]))
        L2.append(int(data1b[i][2]))

    for i in range(repetitions):
        avgX.append(10000*(i + 1))
        sum1, sum2 = 0, 0
        for j in range(k):
            sum1 += L1[i*k + j]
            sum2 += L2[i*k + j]
        avgL1.append(sum1 / k)
        avgL2.append(sum2 / k)

    l1_1 = [ avgL1[n // 10000 - 1] * np.log(np.log(n)) / np.log(n) for n in avgX ]
    l2_1 = [ avgL2[n // 10000 - 1] * np.log(np.log(n)) / np.log(n) for n in avgX ]

    l1_2 = [ avgL1[n // 10000 - 1] * np.log(2) / np.log(np.log(n)) for n in avgX ]
    l2_2 = [ avgL2[n // 10000 - 1] * np.log(2) / np.log(np.log(n)) for n in avgX ]


    makegraph("L1n.png", x, L1, avgX, avgL1, "$L_n^{(1)}$", "50 repetitions", "Number of balls")
    makegraph("L2n.png", x, L2, avgX, avgL2, "$L_n^{(2)}$", "50 repetitions", "Number of balls")

    makegraph_simple("l1_1.png", avgX, l1_1, "$\\frac{l_n^{(1)}}{f_1(n)}$")
    makegraph_simple("l2_1.png", avgX, l2_1, "$\\frac{l_n^{(2)}}{f_1(n)}$")

    makegraph_simple("l1_2.png", avgX, l1_2, "$\\frac{l_n^{(1)}}{f_2(n)}$")
    makegraph_simple("l2_2.png", avgX, l2_2, "$\\frac{l_n^{(2)}}{f_2(n)}$")

    # ex. 2

    data2 = open("2.txt").read().strip().split("\n")

    x = []
    avgX = []
    cmp, s = [], []
    avgCmp, avgS = [], []

    for i in range(len(data2)):
        data2[i] = data2[i].split(" ")

        x.append(int(data2[i][0]))
        cmp.append(int(data2[i][2]))
        s.append(int(data2[i][3]))

    for i in range(repetitions):
        avgX.append(100 * (i + 1))
        sum1, sum2 = 0, 0
        for j in range(k):
            sum1 += cmp[i * k + j]
            sum2 += s[i * k + j]
        avgCmp.append(sum1 / k)
        avgS.append(sum2 / k)

    cmp1 = [ avgCmp[n // 100 - 1] / n for n in avgX ]
    cmp2 = [ avgCmp[n // 100 - 1] / (n * n) for n in avgX ]

    s1 = [ avgS[n // 100 - 1] / n for n in avgX ]
    s2 = [ avgS[n // 100 - 1] / (n * n) for n in avgX ]


    makegraph("cmpn.png", x, cmp, avgX, avgCmp, "$cmp(n)$", "50 repetitions", "Array length")
    makegraph("sn.png", x, s, avgX, avgS, "$s(n)$", "50 repetitions", "Array length")

    makegraph_simple("cmp1.png", avgX, cmp1, "$\\frac{cmp(n)}{n}$")
    makegraph_simple("cmp2.png", avgX, cmp2, "$\\frac{cmp(n)}{n^2}$")

    makegraph_simple("s1.png", avgX, s1, "$\\frac{s(n)}{n}$")
    makegraph_simple("s2.png", avgX, s2, "$\\frac{s(n)}{n^2}$")

    # ex. 3

    data3a = open("3a.txt").read().strip().split("\n") 
    data3b = open("3b.txt").read().strip().split("\n") 

    x = []
    avgX = []
    T1, T2 = [], []
    avgT1, avgT2 = [], []

    for i in range(len(data3a)):
        data3a[i] = data3a[i].split(" ")
        data3b[i] = data3b[i].split(" ")

        x.append(int(data3a[i][0]))
        T1.append(int(data3a[i][2]))
        T2.append(int(data3b[i][2]))

    for i in range(repetitions):
        avgX.append(1000 * (i + 1))
        sum1, sum2 = 0, 0
        for j in range(k):
            sum1 += T1[i * k + j]
            sum2 += T2[i * k + j]
        avgT1.append(sum1 / k)
        avgT2.append(sum2 / k)

    makegraph("T1n.png", x, T1, avgX, avgT1, "$T_n$ for $p = 0.5$", "50 repetitions", "Number of nodes")
    makegraph("T2n.png", x, T2, avgX, avgT2, "$T_n$ for $p = 0.1$", "50 repetitions", "Number of nodes")
