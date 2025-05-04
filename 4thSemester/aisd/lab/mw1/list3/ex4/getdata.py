import subprocess
from statistics import mean
import random

open("data.txt", 'w').close()

# Helper function to run shell commands and extract the required output
def get_comparisons_output(i, program_path, extra_args=None):
    if extra_args is None:
        extra_args = []

    rand = subprocess.run(['./genlist.out', str(i), '1'], capture_output=True, text=True)
    sort = subprocess.run(
        [program_path] + extra_args,
        input=rand.stdout,
        capture_output=True,
        text=True
    )

    output = sort.stdout

    lines = output.strip().splitlines()
    if lines:
        parts = lines[0].split()
        if len(parts) >= 4:
            return [int(parts[1]), int(parts[3])]
        
    return [0, 0]
    
if __name__ == "__main__": 
    n = []
    search_low = [[[], []]]
    search_mid = [[[], []]]
    search_high = [[[], []]]
    search_outside = [[[], []]]
    search_random = [[[], []]]

    for i in range(1000, 100001, 1000):
        print(i)
        n.append(i)

        low = [get_comparisons_output(i, './binsearch.out', extra_args=[str(random.randint(0, i // 100))]) for _ in range(50)]
        mid = [get_comparisons_output(i, './binsearch.out', extra_args=[str(random.randint(12 * i // 25, 13 * i // 25))]) for _ in range(50)]
        high = [get_comparisons_output(i, './binsearch.out', extra_args=[str(random.randint(99 * i // 100, i - 1))]) for _ in range(50)]
        outside = [get_comparisons_output(i, './binsearch.out', extra_args=['-1']) for _ in range(50)]
        rand = [get_comparisons_output(i, './binsearch.out', extra_args=[str(random.randint(0, i - 1))]) for _ in range(50)]

        search_low[0][0].append(mean(x[0] for x in low))
        search_low[0][1].append(mean(x[1] for x in low))
        search_mid[0][0].append(mean(x[0] for x in mid))
        search_mid[0][1].append(mean(x[1] for x in mid))
        search_high[0][0].append(mean(x[0] for x in high))
        search_high[0][1].append(mean(x[1] for x in high))
        search_outside[0][0].append(mean(x[0] for x in outside))
        search_outside[0][1].append(mean(x[1] for x in outside))
        search_random[0][0].append(mean(x[0] for x in rand))
        search_random[0][1].append(mean(x[1] for x in rand))
        

    with open("data.txt", "a") as f:
        for num in n:
            f.write(str(num) + " ")
        f.write("\n")

        for entry in search_low:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in search_mid:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in search_high:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in search_outside:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in search_random:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
