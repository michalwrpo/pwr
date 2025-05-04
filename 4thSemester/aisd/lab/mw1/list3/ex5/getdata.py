import subprocess
from statistics import mean

open("data.txt", 'w').close()

# Helper function to run shell commands and extract the required output
def get_comparisons_output(i, program_path, extra_args=None, inc=False):
    if extra_args is None:
        extra_args = []
    
    if inc:
        rand = subprocess.run(['../ex1/randinc.out', str(i)], capture_output=True, text=True)
    else:
        rand = subprocess.run(['../ex1/rand.out', str(i)], capture_output=True, text=True)

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
    quick = [[[], []], [[], []]]
    dpqs = [[[], []], [[], []]]
    squick = [[[], []], [[], []]]
    sdpqs = [[[], []], [[], []]]

    for i in range(100, 10001, 100):
        print(i)
        n.append(i)

        qs_vals = [get_comparisons_output(i, './quicksort.out') for _ in range(50)]
        dp_vals = [get_comparisons_output(i, './dpqs.out') for _ in range(50)]
        sq_vals = [get_comparisons_output(i, './selectquick.out') for _ in range(50)]
        sd_vals = [get_comparisons_output(i, './selectdpqs.out') for _ in range(50)]

        quick[0][0].append(mean(x[0] for x in qs_vals))
        quick[0][1].append(mean(x[1] for x in qs_vals))
        dpqs[0][0].append(mean(x[0] for x in dp_vals))
        dpqs[0][1].append(mean(x[1] for x in dp_vals))
        squick[0][0].append(mean(x[0] for x in sq_vals))
        squick[0][1].append(mean(x[1] for x in sq_vals))
        sdpqs[0][0].append(mean(x[0] for x in sd_vals))
        sdpqs[0][1].append(mean(x[1] for x in sd_vals))

        qs_vals = [get_comparisons_output(i, './quicksort.out', inc=True) for _ in range(50)]
        dp_vals = [get_comparisons_output(i, './dpqs.out', inc=True) for _ in range(50)]
        sq_vals = [get_comparisons_output(i, './selectquick.out', inc=True) for _ in range(50)]
        sd_vals = [get_comparisons_output(i, './selectdpqs.out', inc=True) for _ in range(50)]

        quick[1][0].append(mean(x[0] for x in qs_vals))
        quick[1][1].append(mean(x[1] for x in qs_vals))
        dpqs[1][0].append(mean(x[0] for x in dp_vals))
        dpqs[1][1].append(mean(x[1] for x in dp_vals))
        squick[1][0].append(mean(x[0] for x in sq_vals))
        squick[1][1].append(mean(x[1] for x in sq_vals))
        sdpqs[1][0].append(mean(x[0] for x in sd_vals))
        sdpqs[1][1].append(mean(x[1] for x in sd_vals))


    with open("data.txt", "a") as f:
        for num in n:
            f.write(str(num) + " ")
        f.write("\n")

        for entry in quick:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in dpqs:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in squick:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in sdpqs:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
