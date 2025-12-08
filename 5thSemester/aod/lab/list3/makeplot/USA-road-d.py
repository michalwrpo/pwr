import os
import re
import matplotlib.pyplot as plt
import numpy as np

# -----------------------------
# CONFIGURATION
# -----------------------------
DATA_CAT = "USA-road-d"
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
# { "d": [(region, timeMs), ...], ... }
data = {k: [] for k in ALGORITHMS}
data1 = {k: [] for k in ALGORITHMS}

# Pattern: USA-road-d-d.BAY.0.ss.res
pattern0 = re.compile(r"USA-road-d-([dlr])\.([A-Z]+)\.0\.ss\.res$")
pattern1 = re.compile(r"USA-road-d-([dlr])\.([A-Z]+)\.1\.ss\.res$")

for fname in sorted(os.listdir(OUTPUT_DIR)):
    m = pattern0.match(fname)
    if not m:
        continue

    algo = m.group(1)
    region = m.group(2)

    time_ms = None

    with open(os.path.join(OUTPUT_DIR, fname)) as f:
        for line in f:
            if line.startswith("t "):
                time_ms = float(line.split()[1])
                break

    if time_ms is not None:
        data[algo].append((region, time_ms))

for fname in sorted(os.listdir(OUTPUT_DIR)):
    m = pattern1.match(fname)
    if not m:
        continue

    algo = m.group(1)
    region = m.group(2)

    time_ms = None

    with open(os.path.join(OUTPUT_DIR, fname)) as f:
        for line in f:
            if line.startswith("t "):
                time_ms = float(line.split()[1])
                break

    if time_ms is not None:
        data1[algo].append((region, time_ms))

# -----------------------------
# PREPARE HISTOGRAM DATA
# -----------------------------
regions = sorted({r for algo in data for (r, _) in data[algo]})
x = np.arange(len(regions))

bar_width = 0.25

plt.figure(figsize=(14, 8))

# Shift positions for each algorithm
for i, algo in enumerate(ALGORITHMS):
    times = []
    for region in regions:
        # find matching entry
        t = next((v for (reg, v) in data[algo] if reg == region), None)
        times.append(t if t is not None else 0)
    plt.bar(x + i * bar_width, times, width=bar_width,
            color=ALGO_COLORS[algo], label=ALGO_NAMES[algo])

plt.xticks(x + bar_width, regions, rotation=20)
plt.xlabel("Region")
plt.ylabel("Time (ms)")
plt.title(f"{DATA_CAT} – Runtime Histogram - Multiple sources")
plt.legend()
plt.grid(axis="y", linestyle="--", alpha=0.5)

outpath = os.path.join(PLOT_DIR, f"{DATA_CAT}_hist.png")
plt.savefig(outpath)
print(f"Saved: {outpath}")

# -----------------------------
# LOG-SCALE HISTOGRAM
# -----------------------------
plt.yscale("log")
outpath = os.path.join(PLOT_DIR, f"{DATA_CAT}_hist_log.png")
plt.savefig(outpath)
plt.close()

print(f"Saved: {outpath}")

# -----------------------------
# SINGLE SOURCE
# -----------------------------
regions = sorted({r for algo in data1 for (r, _) in data1[algo]})
x = np.arange(len(regions))

bar_width = 0.25

plt.figure(figsize=(14, 8))

# Shift positions for each algorithm
for i, algo in enumerate(ALGORITHMS):
    times = []
    for region in regions:
        # find matching entry
        t = next((v for (reg, v) in data1[algo] if reg == region), None)
        times.append(t if t is not None else 0)
    plt.bar(x + i * bar_width, times, width=bar_width,
            color=ALGO_COLORS[algo], label=ALGO_NAMES[algo])

plt.xticks(x + bar_width, regions, rotation=20)
plt.xlabel("Region")
plt.ylabel("Time (ms)")
plt.title(f"{DATA_CAT} – Runtime Histogram - Single source")
plt.legend()
plt.grid(axis="y", linestyle="--", alpha=0.5)

outpath = os.path.join(PLOT_DIR, f"{DATA_CAT}_1_hist.png")
plt.savefig(outpath)
print(f"Saved: {outpath}")

# -----------------------------
# LOG-SCALE HISTOGRAM
# -----------------------------
plt.yscale("log")
outpath = os.path.join(PLOT_DIR, f"{DATA_CAT}_1_hist_log.png")
plt.savefig(outpath)
plt.close()

print(f"Saved: {outpath}")
