import os
import re
import matplotlib.pyplot as plt

# -----------------------------
# CONFIGURATION
# -----------------------------
DATA_CAT = "Square-n"
OUTPUT_DIR = f"outputs/{DATA_CAT}"
ALGORITHMS = ["d", "l", "r"]   # d=dijkstra, l=dial, r=radixheap
ALGO_NAMES = {
    "d": "Dijkstra",
    "l": "Dial",
    "r": "Radix_Heap"
}
ALGO_COLORS = {
    "d": "blue",
    "l": "green",
    "r": "red",
}

PLOT_DIR = "plots"
os.makedirs(PLOT_DIR, exist_ok=True)

# -----------------------------
# DATA EXTRACTION
# -----------------------------
# { "d": [(maxWeight, timeMs), ...], ... }
data = {k: [] for k in ALGORITHMS}
data1 = {k: [] for k in ALGORITHMS}

for fname in sorted(os.listdir(OUTPUT_DIR)):
    # match: Square-n-{d|l|r}.i.0.ss.res
    m = re.match(r"Square-n-([dlr])\.(\d+)\.0\.ss\.res$", fname)
    if not m:
        continue

    algo = m.group(1)
    n = int(m.group(2)) 

    time_ms = None

    with open(os.path.join(OUTPUT_DIR, fname)) as f:
        for line in f:
            if line.startswith("t "):
                time_ms = float(line.split()[1])
                break

    if time_ms is not None:
        data[algo].append((n, time_ms))

for fname in sorted(os.listdir(OUTPUT_DIR)):
    # match: Square-n-{d|l|r}.i.1.ss.res
    m = re.match(r"Square-n-([dlr])\.(\d+)\.1\.ss\.res$", fname)
    if not m:
        continue

    algo = m.group(1)
    n = int(m.group(2)) 

    time_ms = None

    with open(os.path.join(OUTPUT_DIR, fname)) as f:
        for line in f:
            if line.startswith("t "):
                time_ms = float(line.split()[1])
                break

    if time_ms is not None:
        data1[algo].append((n, time_ms))

# -----------------------------
# PLOTS
# -----------------------------
plt.figure(figsize=(12, 8))

max_vals = []

for algo in ALGORITHMS:
    points = sorted(data[algo])
    points1 = sorted(data1[algo])
    if not points or not points1:
        print(f"No data for algorithm {algo}")
        continue

    xs  = [p[0] for p in points]
    ys  = [p[1] for p in points]
    xs1 = [p[0] for p in points1]
    ys1 = [p[1] for p in points1]

    max_vals.append(max(max(ys), max(ys1)))
    color = ALGO_COLORS.get(algo, "black")

    # Random sources (solid)
    plt.plot(xs, ys, marker="o", linestyle="-", color=color,
             label=f"{ALGO_NAMES[algo]} – 5 random sources")

    # Single sources (dashed)
    plt.plot(xs1, ys1, marker="o", linestyle="--", color=color,
             label=f"{ALGO_NAMES[algo]} – single source")

# Global settings
top_lim =  min(1.1*max(max_vals), 10*min(max_vals))
plt.ylim(bottom=-0.05*top_lim, top=top_lim)
plt.title(f"{DATA_CAT} – Running Time vs Maximum Edge Weight $(4^i)$")
plt.xlabel("$i$")
plt.ylabel("Time (ms)")
plt.grid(True)
plt.legend()

outpath = os.path.join(PLOT_DIR, f"{DATA_CAT}.png")
plt.savefig(outpath)

plt.yscale("log")
top_lim =  1.1*max(max_vals)
plt.ylim(top=top_lim)

outpath = os.path.join(PLOT_DIR, f"{DATA_CAT}_log.png")
plt.savefig(outpath)

plt.close()

print(f"Saved combined plot with colors: {outpath}")
