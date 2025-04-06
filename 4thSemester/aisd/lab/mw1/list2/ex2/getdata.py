import subprocess
from statistics import mean

open("data.txt", 'w').close()

# Helper function to run shell commands and extract the required output
def get_comparisons_output(i, program_path, toomuch=True, extra_args=None):
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

    if toomuch:
        for line in output.splitlines():
            if "Comparisons" in line:
                parts = line.split()
                if len(parts) >= 4:
                    return [int(parts[1]), int(parts[3])]
        return [0, 0]  # fallback if not found
    else:
        lines = output.strip().splitlines()
        if lines:
            parts = lines[0].split()
            if len(parts) >= 4:
                return [int(parts[1]), int(parts[3])]
        return [0, 0]
    
if __name__ == "__main__": 
    # --- Short range (10 to 50) ---
    nshort = []
    insort = [[[], []], [[], []], [[], []]]
    quick = [[[], []], [[], []], [[], []]]
    hybrid = [[[], []], [[], []], [[], []]]
    mine = [[[], []], [[], []], [[], []]]
    dpqs = [[[], []], [[], []], [[], []]]

    # --- Short range ---
    for i in range(10, 60, 10):
        print(i)
        nshort.append(i)

        # 1 repetition (just append as-is)
        ins = get_comparisons_output(i, '../ex1/insort.out')
        qs = get_comparisons_output(i, '../ex1/quicksort.out')
        hs = get_comparisons_output(i, '../ex1/hybridsort.out', extra_args=['5'])
        my = get_comparisons_output(i, '../ex3/mysort.out')
        dp = get_comparisons_output(i, '../ex4/dpqs.out')

        insort[0][0].append(ins[0])
        insort[0][1].append(ins[1])
        quick[0][0].append(qs[0])
        quick[0][1].append(qs[1])
        hybrid[0][0].append(hs[0])
        hybrid[0][1].append(hs[1])
        mine[0][0].append(my[0])
        mine[0][1].append(my[1])
        dpqs[0][0].append(dp[0])
        dpqs[0][1].append(dp[1])

        # 10 repetitions
        ins_vals = [get_comparisons_output(i, '../ex1/insort.out') for _ in range(10)]
        qs_vals = [get_comparisons_output(i, '../ex1/quicksort.out') for _ in range(10)]
        hs_vals = [get_comparisons_output(i, '../ex1/hybridsort.out', extra_args=['5']) for _ in range(10)]
        my_vals = [get_comparisons_output(i, '../ex3/mysort.out') for _ in range(10)]
        dp_vals = [get_comparisons_output(i, '../ex4/dpqs.out') for _ in range(10)]

        insort[1][0].append(mean(x[0] for x in ins_vals))
        insort[1][1].append(mean(x[1] for x in ins_vals))
        quick[1][0].append(mean(x[0] for x in qs_vals))
        quick[1][1].append(mean(x[1] for x in qs_vals))
        hybrid[1][0].append(mean(x[0] for x in hs_vals))
        hybrid[1][1].append(mean(x[1] for x in hs_vals))
        mine[1][0].append(mean(x[0] for x in my_vals))
        mine[1][1].append(mean(x[1] for x in my_vals))
        dpqs[1][0].append(mean(x[0] for x in dp_vals))
        dpqs[1][1].append(mean(x[1] for x in dp_vals))

        # 100 repetitions
        ins_vals = [get_comparisons_output(i, '../ex1/insort.out') for _ in range(100)]
        qs_vals = [get_comparisons_output(i, '../ex1/quicksort.out') for _ in range(100)]
        hs_vals = [get_comparisons_output(i, '../ex1/hybridsort.out', extra_args=['5']) for _ in range(100)]
        my_vals = [get_comparisons_output(i, '../ex3/mysort.out') for _ in range(100)]
        dp_vals = [get_comparisons_output(i, '../ex4/dpqs.out') for _ in range(100)]

        insort[2][0].append(mean(x[0] for x in ins_vals))
        insort[2][1].append(mean(x[1] for x in ins_vals))
        quick[2][0].append(mean(x[0] for x in qs_vals))
        quick[2][1].append(mean(x[1] for x in qs_vals))
        hybrid[2][0].append(mean(x[0] for x in hs_vals))
        hybrid[2][1].append(mean(x[1] for x in hs_vals))
        mine[2][0].append(mean(x[0] for x in my_vals))
        mine[2][1].append(mean(x[1] for x in my_vals))
        dpqs[2][0].append(mean(x[0] for x in dp_vals))
        dpqs[2][1].append(mean(x[1] for x in dp_vals))

    with open("data.txt", "a") as f:
        for num in nshort:
            f.write(str(num) + " ")
        f.write("\n")

        for entry in insort:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in quick:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in hybrid:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in mine:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
        
        for entry in dpqs:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

    nlong = []
    quick_l = [[[], []], [[], []], [[], []]]
    hybrid_l = [[[], []], [[], []], [[], []]]
    mine_l = [[[], []], [[], []], [[], []]]
    dpqs_l = [[[], []], [[], []], [[], []]]


    # --- Long range ---
    for i in range(1000, 50001, 1000):
        print(i)
        nlong.append(i)

        # 1 repetition
        qs = get_comparisons_output(i, '../ex1/quicksort.out', False)
        hs = get_comparisons_output(i, '../ex1/hybridsort.out', False, extra_args=['5'])
        my = get_comparisons_output(i, '../ex3/mysort.out', False)
        dp = get_comparisons_output(i, '../ex4/dpqs.out', False)

        quick_l[0][0].append(qs[0])
        quick_l[0][1].append(qs[1])
        hybrid_l[0][0].append(hs[0])
        hybrid_l[0][1].append(hs[1])
        mine_l[0][0].append(my[0])
        mine_l[0][1].append(my[1])
        dpqs_l[0][0].append(dp[0])
        dpqs_l[0][1].append(dp[1])

        # 10 repetitions
        qs_vals = [get_comparisons_output(i, '../ex1/quicksort.out', False) for _ in range(10)]
        hs_vals = [get_comparisons_output(i, '../ex1/hybridsort.out', False, extra_args=['5']) for _ in range(10)]
        my_vals = [get_comparisons_output(i, '../ex3/mysort.out', False) for _ in range(10)]
        dp_vals = [get_comparisons_output(i, '../ex4/dpqs.out', False) for _ in range(10)]

        quick_l[1][0].append(mean(x[0] for x in qs_vals))
        quick_l[1][1].append(mean(x[1] for x in qs_vals))
        hybrid_l[1][0].append(mean(x[0] for x in hs_vals))
        hybrid_l[1][1].append(mean(x[1] for x in hs_vals))
        mine_l[1][0].append(mean(x[0] for x in my_vals))
        mine_l[1][1].append(mean(x[1] for x in my_vals))
        dpqs_l[1][0].append(mean(x[0] for x in dp_vals))
        dpqs_l[1][1].append(mean(x[1] for x in dp_vals))

        # 100 repetitions
        qs_vals = [get_comparisons_output(i, '../ex1/quicksort.out', False) for _ in range(100)]
        hs_vals = [get_comparisons_output(i, '../ex1/hybridsort.out', False, extra_args=['5']) for _ in range(100)]
        my_vals = [get_comparisons_output(i, '../ex3/mysort.out') for _ in range(100)]
        dp_vals = [get_comparisons_output(i, '../ex4/dpqs.out', False) for _ in range(100)]

        quick_l[2][0].append(mean(x[0] for x in qs_vals))
        quick_l[2][1].append(mean(x[1] for x in qs_vals))
        hybrid_l[2][0].append(mean(x[0] for x in hs_vals))
        hybrid_l[2][1].append(mean(x[1] for x in hs_vals))
        mine_l[2][0].append(mean(x[0] for x in my_vals))
        mine_l[2][1].append(mean(x[1] for x in my_vals))
        dpqs_l[2][0].append(mean(x[0] for x in dp_vals))
        dpqs_l[2][1].append(mean(x[1] for x in dp_vals))

    with open("data.txt", "a") as f:
        for num in nlong:
            f.write(str(num) + " ")
        f.write("\n")

        for entry in quick_l:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in hybrid_l:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")

        for entry in mine_l:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
        
        for entry in dpqs_l:
            for category in entry:
                for num in category:
                    f.write(str(num) + " ")
                f.write("\n")
