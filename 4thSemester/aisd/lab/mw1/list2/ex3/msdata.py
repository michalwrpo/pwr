import subprocess
from statistics import mean

open("msdata.txt", 'w').close()

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
            return [int(parts[1]), int(parts[3])]
    return [0, 0]
    
if __name__ == "__main__": 
    merge = [[[], []], [[], []], [[], []]]

    for i in range(1000, 50001, 1000):
        print(i)

        # 1 repetition (just append as-is)
        ms = get_comparisons_output(i, './mergesort.out')

        merge[0][0].append(ms[0])
        merge[0][1].append(ms[1])

        # 10 repetitions
        ms = [get_comparisons_output(i, './mergesort.out') for _ in range(10)]

        merge[1][0].append(mean(x[0] for x in ms))
        merge[1][1].append(mean(x[1] for x in ms))

        # 100 repetitions
        ms = [get_comparisons_output(i, './mergesort.out') for _ in range(100)]

        merge[2][0].append(mean(x[0] for x in ms))
        merge[2][1].append(mean(x[1] for x in ms))


    with open("msdata.txt", "a") as f:
        for entry in merge:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
