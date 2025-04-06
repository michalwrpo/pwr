import subprocess
from statistics import mean
import numpy as np


# Helper function to run shell commands and extract the required output
def get_comparisons_output(i, program_path):

    rand = subprocess.run(['../ex1/rand.out', str(i)], capture_output=True, text=True)
    sort = subprocess.run(
        [program_path],
        input=rand.stdout,
        capture_output=True,
        text=True
    )

    output = sort.stdout

    lines = output.strip().splitlines()
    if lines:
        parts = lines[0].split()
        if len(parts) >= 4:
            return int(parts[1])
    return 0
    
if __name__ == "__main__": 
    dpqs = []

    for i in range(10000, 100001, 10000):
        dp = [get_comparisons_output(i, './dpqs.out') for _ in range(100)]

        dpqs.append(mean(dp))

    normalized = []
    log = np.log2(range(10000, 100001, 10000))

    for i in range(len(dpqs)):
        n = dpqs[i]
        
        normalized.append(n/(10000*(i+1) * log[i]))

    print("Calculating constant (c) in Dual-Pivot Quick Sort.")
    print("For each n repeating 100 times and taking the average.")

    for i in range(len(dpqs)):
        print("n = " + str(10000*(i+1)) + ": c = " + str(normalized[i]))

    print("Average: ", mean(normalized))

    
