import numpy as np
import matplotlib.pyplot as plt
from typing import Callable, List

def f1(x: float) -> float:
    return x**(1/3)

def f2(x: float) -> float:
    return np.sin(x)

def f3(x: float) -> float:
    return 4*x*(1-x)**3

def fpi(x: float) -> float:
    return 4*np.sqrt(1-x**2);

def makegraph(fileName: str, x: List[int], y: List[float], avgX: List[int], avgY: List[float], trueValue: float, title: str, subtitle: str) -> None:
    plt.clf()
    plt.grid(True)
    plt.scatter(x, y, c='b', s=1, label="Approximated value")
    plt.scatter(avgX, avgY, c='r', s=8, label="Mean approximated value")
    plt.axhline(trueValue, c='g', label="True value")
    plt.xlabel('Number of points')
    plt.ylabel('Approximated value')
    plt.suptitle(title)
    plt.title(subtitle, fontsize=10)
    plt.legend()
    plt.savefig(fileName)

def approximate(f: Callable, n: int, a: float, b: float, M: float) -> float:
    if not callable(f):
        raise TypeError("Function should be callable")
    if (a > b):
        raise ValueError("Beginning of an interval should be smaller than its end")
    
    C = 0
    for i in range(n):
        if M * np.random.random_sample() < f(a + (b - a) * np.random.random_sample()):
            C += 1
    return C/n * M * (b - a)

def simulate(f: Callable, a: float, b: float, M: float, Nmin: int, Nmax: int, Nstep: int, K: int, trueValue: float, plotTitle: str, plotSubtitle: str, fileName: str) -> None:
    if not callable(f):
        raise TypeError("Function should be callable")
    if (Nmax - Nmin) % Nstep != 0:
        raise ValueError("Range of number of tests should be divisible by step")
    if (a > b):
        raise ValueError("Beginning of an interval should be smaller than its end")
    
    resultsX = []
    resultsY = []
    avgX = []
    avgY = []
    for n in range(Nmin, Nmax + Nstep, Nstep):
        sumY = 0
        for i in range(K):
            print(f'Simulating {f.__name__} for n={n}, test {i+1}... ', end='')
            y = approximate(f, n, a, b, M)
            resultsX.append(n)
            resultsY.append(y)
            sumY += y
            print(f'Result: {y:10.5f}')
        avgX.append(n)
        avgY.append(sumY/K)

    makegraph(fileName, resultsX, resultsY, avgX, avgY, trueValue, plotTitle, plotSubtitle)

    return None

def quickSimulate(f: Callable, a: float, b: float, M: float, K: int, trueValue: float, fName: str) -> None:
    simulate(f, a, b, M, 50, 5000, 50, K, trueValue, f"Approximation of {fName}", "$n_{min} = 50, n_{max} = 5000, n_{step} = 50, K = $" + f"${K}$", f.__name__ + "k" + str(len(str(K))) + ".png")


if __name__ == "__main__":
    quickSimulate(f1, 0, 8, 4, 5, 12, "$\sqrt[3]{x}$")
    quickSimulate(f1, 0, 8, 4, 50, 12, "$\sqrt[3]{x}$")
    quickSimulate(f2, 0, np.pi, 1.5, 5, 2, "$\sin{x}$")
    quickSimulate(f2, 0, np.pi, 1.5, 50, 2, "$\sin{x}$")
    quickSimulate(f3, 0, 1, 0.5, 5, 0.2, "$4x(1-x)^3$")
    quickSimulate(f3, 0, 1, 0.5, 50, 0.2, "$4x(1-x)^3$")
    quickSimulate(fpi, 0, 1, 6, 5, np.pi, "$\pi$ using $4\sqrt{1-x^2}$")
    quickSimulate(fpi, 0, 1, 6, 50, np.pi, "$\pi$ using $4\sqrt{1-x^2}$")