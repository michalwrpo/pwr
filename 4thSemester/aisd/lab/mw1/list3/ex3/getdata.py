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
    sel3 = [[[], []], [[], []], [[], []]]
    sel5 = [[[], []], [[], []], [[], []]]
    sel7 = [[[], []], [[], []], [[], []]]
    sel9 = [[[], []], [[], []], [[], []]]

    for i in range(100, 50001, 100):
        print(i)
        n.append(i)

        sel3_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['3', '1']) for _ in range(50)]
        sel5_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['5', '1']) for _ in range(50)]
        sel7_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['7', '1']) for _ in range(50)]
        sel9_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['9', '1']) for _ in range(50)]

        sel3[0][0].append(mean(x[0] for x in sel3_vals))
        sel3[0][1].append(mean(x[1] for x in sel3_vals))
        sel5[0][0].append(mean(x[0] for x in sel5_vals))
        sel5[0][1].append(mean(x[1] for x in sel5_vals))
        sel7[0][0].append(mean(x[0] for x in sel7_vals))
        sel7[0][1].append(mean(x[1] for x in sel7_vals))
        sel9[0][0].append(mean(x[0] for x in sel9_vals))
        sel9[0][1].append(mean(x[1] for x in sel9_vals))


    for i in range(100, 50001, 100):
        print(i)

        sel3_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['3', str(i // 2)]) for _ in range(50)]
        sel5_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['5', str(i // 2)]) for _ in range(50)]
        sel7_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['7', str(i // 2)]) for _ in range(50)]
        sel9_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['9', str(i // 2)]) for _ in range(50)]

        sel3[1][0].append(mean(x[0] for x in sel3_vals))
        sel3[1][1].append(mean(x[1] for x in sel3_vals))
        sel5[1][0].append(mean(x[0] for x in sel5_vals))
        sel5[1][1].append(mean(x[1] for x in sel5_vals))
        sel7[1][0].append(mean(x[0] for x in sel7_vals))
        sel7[1][1].append(mean(x[1] for x in sel7_vals))
        sel9[1][0].append(mean(x[0] for x in sel9_vals))
        sel9[1][1].append(mean(x[1] for x in sel9_vals))

    for i in range(100, 50001, 100):
        print(i)

        sel3_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['3', str(3 * i // 4)]) for _ in range(50)]
        sel5_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['5', str(3 * i // 4)]) for _ in range(50)]
        sel7_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['7', str(3 * i // 4)]) for _ in range(50)]
        sel9_vals = [get_comparisons_output(i, '../ex3/select.out', extra_args=['9', str(3 * i // 4)]) for _ in range(50)]

        sel3[2][0].append(mean(x[0] for x in sel3_vals))
        sel3[2][1].append(mean(x[1] for x in sel3_vals))
        sel5[2][0].append(mean(x[0] for x in sel5_vals))
        sel5[2][1].append(mean(x[1] for x in sel5_vals))
        sel7[2][0].append(mean(x[0] for x in sel7_vals))
        sel7[2][1].append(mean(x[1] for x in sel7_vals))
        sel9[2][0].append(mean(x[0] for x in sel9_vals))
        sel9[2][1].append(mean(x[1] for x in sel9_vals))

    with open("data.txt", "a") as f:
        for num in n:
            f.write(str(num) + " ")
        f.write("\n")

        for entry in sel3:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in sel5:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in sel7:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in sel9:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
