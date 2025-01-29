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
