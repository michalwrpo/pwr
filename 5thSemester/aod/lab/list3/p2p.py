import os
import re

P2P_DIR = "outputs/p2p"
ALG = {
    "d": "Dijkstra",
    "l": "Dial",
    "r": "RadixHeap"
}

# Regex to detect ending type
pattern0 = re.compile(r"\.0\.p2p\.res$")
pattern1 = re.compile(r"\.1\.p2p\.res$")

print("Processing p2p/ directory...\n")

for fname in sorted(os.listdir(P2P_DIR)):
    fpath = os.path.join(P2P_DIR, fname)

    if not fname.endswith(".p2p.res"):
        continue

    is_type0 = bool(pattern0.search(fname))
    is_type1 = bool(pattern1.search(fname))

    time_ms = None
    query = None  # (start, end, dist)

    with open(fpath) as f:
        for line in f:
            line = line.strip()

            if line.startswith("t "):
                # t <time_ms>
                time_ms = float(line.split()[1])

            elif line.startswith("q ") and is_type1:
                # q start end dist
                parts = line.split()
                if len(parts) == 4:
                    _, s, e, d = parts
                    query = (int(s), int(e), int(d))

    name = fname.split(".")[0]
    gtype = name[:-2]
    alg = ALG[name[-1]]



    if is_type1:
        if query:
            s, e, d = query

            print(f"{gtype} - {alg} & {s} & {e} & {d} & {time_ms} \\\\")

    # if is_type0:
    #     print(f"{gtype} - {alg} & {time_ms} \\\\")

