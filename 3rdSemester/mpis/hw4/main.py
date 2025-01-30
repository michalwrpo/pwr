import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import Normal
import math

if __name__=="__main__":
    for N in [5, 10, 15, 20, 25, 100]:
        sum = 0
        x = []
        y = []
        xcdf = np.linspace(-N-1, N+1)
        stdcdf = Normal(sigma=np.sqrt(N)).cdf(xcdf)
        for k in range(0, N+1):
            sum += 1/(2**N) * math.comb(N, k)
            x.append(2*k - N)
            y.append(sum)

        x.append(N+2)
        plt.clf()
        plt.stairs(y, edges=x, label="$S_{" + str(N) + "}$ CDF")
        plt.plot(xcdf, stdcdf, "k--", linewidth=1.5, label="Normal distribution CDF")
        plt.xlim(left=-N-1, right=N+1)
        plt.legend()
        plt.title("$S_{" + str(N) + "}$")
        plt.savefig("z2n" + str(N) + ".png")

    data = open("ex3.txt").read().strip().split("\n")
    data = [float(vals.split(" ")[1]) for vals in data]
    asinx = np.linspace(0.01, 0.99)
    asin = 1/np.pi / (np.sqrt((1-asinx)*asinx))
    for i in range(3):
        N = 10**(i + 2)
        nums = data[5000 * i:5000 * (i + 1)]
        plt.clf()
        plt.hist(nums, bins=20, range=(0, 1), density=True, label=f"$P_{{{N}}}$")
        plt.xlim(left=0.0, right=1.0)
        plt.plot(asinx, asin, linewidth=1.5, label="$\\frac{1}{\\pi\\sqrt{(1-x)x}}$ - PDF of $\\frac{2}{\\pi}\\arcsin(\\sqrt{x})$")
        plt.title(f"Histogram of $P_{{{N}}}$")
        plt.grid(True)
        plt.legend()
        plt.savefig("z3n" + str(N) + ".png")
            