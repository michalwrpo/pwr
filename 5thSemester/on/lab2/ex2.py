# Michał Waluś 279695

from matplotlib import pyplot as plt
import numpy as np

def f(x):
    return np.e ** x * np.log(1 + np.e ** (-x))

if __name__ == "__main__":
    plt.rcParams.update({
        "text.usetex": True,
        "font.family": "Helvetica"
    })

    xs = np.linspace(-10, 50, 100000)
    ys = [f(x) for x in xs]
    plt.plot(xs, ys, label="$y = e^x\\ln \\left( 1 + e^{-x}\\right)$")
    plt.legend()
    plt.savefig("ex2mpl.png")