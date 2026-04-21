import matplotlib.pyplot as plt

def plot_tsp_solution(coords_file, solution_file):
    nodes = {}
    
    with open(coords_file, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            
            if not line[0].isdigit():
                continue
            
            parts = line.split()
            if len(parts) >= 3:
                idx = int(parts[0]) - 1 
                x = float(parts[1])
                y = float(parts[2])
                nodes[idx] = (x, y)

    permutation = []
    with open(solution_file, 'r') as f:
        lines = f.readlines()
        for i, line in enumerate(lines):
            if line.startswith("Best solution"):
                if i + 1 < len(lines):
                    sol_line = lines[i + 1].strip()
                    permutation = [int(val) for val in sol_line.split()]
                break
    
    if not permutation:
        print("Error: Could not find the solution permutation in the file.")
        return

    ordered_x = []
    ordered_y = []
    
    for idx in permutation:
        if idx in nodes:
            ordered_x.append(nodes[idx][0])
            ordered_y.append(nodes[idx][1])
        else:
            print(f"Warning: Index {idx} found in solution but not in coordinates file.")

    if ordered_x and ordered_y:
        ordered_x.append(ordered_x[0])
        ordered_y.append(ordered_y[0])

    plt.figure(figsize=(10, 6))
    
    plt.plot(ordered_x, ordered_y, marker='o', linestyle='-', color='dodgerblue', markersize=5, linewidth=1.5)
        
    sfilesplit = solution_file[3:-4].split("out/")
    outname = sfilesplit[0] + sfilesplit[1].split(".")[0] + ".png"
    
    title = sfilesplit[0][:2] + " " + sfilesplit[0][2] + " " + sfilesplit[1]

    plt.title(title)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.grid(True, linestyle='--', alpha=0.6)
    
    plt.tight_layout()
    plt.savefig(outname)

if __name__ == "__main__":
    dirs = ["ex1_out/", "ex2_out/", "ex3_out/"]
    files = ["wi29.out", "dj38.out", "qa194.out", "uy734.out", "zi929.out", "mu1979.out"]

    for dir in dirs:
        for file in files:
            plot_tsp_solution("../data/" + file.split(".")[0] + ".tsp", "../" + dir + file)

