import subprocess
from statistics import mean

open("data.txt", 'w').close()

# Helper function to run shell commands and extract the required output
def get_comparisons_output(i, program_path, extra_args=None):
    if extra_args is None:
        extra_args = []

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
    rsel = [[[], []], [[], []], [[], []]]
    sel = [[[], []], [[], []], [[], []]]

    for i in range(100, 50001, 100):
        print(i)
        n.append(i)

        rsel_vals = [get_comparisons_output(i, '../ex1/randomselect.out', extra_args=[str(i // 20)]) for _ in range(50)]
        sel_vals = [get_comparisons_output(i, '../ex1/select.out', extra_args=[str(i // 20)]) for _ in range(50)]

        rsel[0][0].append(mean(x[0] for x in rsel_vals))
        rsel[0][1].append(mean(x[1] for x in rsel_vals))
        sel[0][0].append(mean(x[0] for x in sel_vals))
        sel[0][1].append(mean(x[1] for x in sel_vals))

    for i in range(100, 50001, 100):
        print(i)

        rsel_vals = [get_comparisons_output(i, '../ex1/randomselect.out', extra_args=[str(i // 2)]) for _ in range(50)]
        sel_vals = [get_comparisons_output(i, '../ex1/select.out', extra_args=[str(i // 2)]) for _ in range(50)]

        rsel[1][0].append(mean(x[0] for x in rsel_vals))
        rsel[1][1].append(mean(x[1] for x in rsel_vals))
        sel[1][0].append(mean(x[0] for x in sel_vals))
        sel[1][1].append(mean(x[1] for x in sel_vals))

    for i in range(100, 50001, 100):
        print(i)

        rsel_vals = [get_comparisons_output(i, '../ex1/randomselect.out', extra_args=[str(3 * i // 4)]) for _ in range(50)]
        sel_vals = [get_comparisons_output(i, '../ex1/select.out', extra_args=[str(3 * i // 4)]) for _ in range(50)]

        rsel[2][0].append(mean(x[0] for x in rsel_vals))
        rsel[2][1].append(mean(x[1] for x in rsel_vals))
        sel[2][0].append(mean(x[0] for x in sel_vals))
        sel[2][1].append(mean(x[1] for x in sel_vals))


    with open("data.txt", "a") as f:
        for num in n:
            f.write(str(num) + " ")
        f.write("\n")

        for entry in rsel:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in sel:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
