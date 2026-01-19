import matplotlib.pyplot as plt
import numpy as np
import os

def parse_files():
    """
    Reads files results_k_i.txt for k in [3, 10] and i in [1, k].
    Returns a nested dictionary: data[k][i] = {'edges': [], 'times': []}
    """
    data = {}
    
    # Iterate over the specified range of k
    for k in range(3, 11):
        data[k] = {}
        for i in range(1, k + 1):
            filename = f"output/results_{k}_{i}.txt"
            
            # Initialize lists for this k, i pair
            data[k][i] = {'edges': [], 'times': []}
            
            if not os.path.exists(filename):
                # print(f"Warning: {filename} not found.") # Uncomment to debug
                continue

            try:
                with open(filename, 'r') as f:
                    lines = f.readlines()
                    
                    idx = 0
                    while idx < len(lines) - 1:
                        line1 = lines[idx].strip()
                        line2 = lines[idx+1].strip()
                        
                        if not line1 or not line2:
                            idx += 1
                            continue

                        if line1.startswith("Edges:"):
                            edge_val = int(line1.split(":")[1].strip())
                            data[k][i]['edges'].append(edge_val)
                        
                        try:
                            time_val = float(line2)
                            data[k][i]['times'].append(time_val)
                        except ValueError:
                            pass # Skip malformed lines

                        idx += 2
            except Exception as e:
                print(f"Error reading {filename}: {e}")
                
    return data

def plot_matching_size_vs_i(data):
    """
    Generates one graph for each k.
    X-axis: i
    Y-axis: Maximal Matching Size (Edges)
    """
    output_dir = "plots"
    
    for k in sorted(data.keys()):
        i_values = []
        means = []
        mins = []
        maxs = []
        
        # Collect data for this k across all i
        for i in sorted(data[k].keys()):
            edges = data[k][i]['edges']
            if not edges: continue
            
            i_values.append(i)
            means.append(np.mean(edges))
            mins.append(np.min(edges))
            maxs.append(np.max(edges))
            
        if not i_values: continue

        # Plotting
        plt.figure(figsize=(8, 5))
        plt.plot(i_values, means, marker='o', color='b', label='Average Edges')
        plt.fill_between(i_values, mins, maxs, color='b', alpha=0.2, label='Min-Max Range')
        
        plt.title(f'Maximal Matching Size vs i (Fixed k={k})')
        plt.xlabel('Degree i')
        plt.ylabel('Number of Edges')
        plt.grid(True, linestyle='--', alpha=0.6)
        plt.xticks(i_values)
        plt.legend()
        
        filename = os.path.join(output_dir, f"matching_size_k_{k}.png")
        plt.savefig(filename)
        plt.close()
        print(f"Generated: {filename}")

def plot_execution_time_vs_k(data):
    """
    Generates one graph for each i.
    X-axis: k
    Y-axis: Execution Time
    """
    output_dir = "plots"
    
    # Find all unique i values present across all k
    all_is = set()
    for k in data:
        all_is.update(data[k].keys())
        
    for i in sorted(all_is):
        k_values = []
        means = []
        mins = []
        maxs = []
        
        # Collect data for this i across all k where k >= i
        for k in sorted(data.keys()):
            if i in data[k]:
                times = data[k][i]['times']
                if not times: continue
                
                k_values.append(k)
                means.append(np.mean(times))
                mins.append(np.min(times))
                maxs.append(np.max(times))
        
        if not k_values: continue

        # Plotting
        plt.figure(figsize=(8, 5))
        plt.plot(k_values, means, marker='s', color='r', label='Average Time')
        plt.fill_between(k_values, mins, maxs, color='r', alpha=0.2, label='Min-Max Range')
        
        plt.title(f'Execution Time vs k (Fixed i={i})')
        plt.xlabel('Graph Size Parameter k')
        plt.ylabel('Time (seconds)')
        
        plt.yscale('log') 
        plt.ylabel('Time (seconds) - Log Scale')
        
        plt.grid(True, linestyle='--', alpha=0.6, which="both")
        plt.xticks(k_values)
        plt.legend()
        
        filename = os.path.join(output_dir, f"execution_time_i_{i}.png")
        plt.savefig(filename)
        plt.close()
        print(f"Generated: {filename}")

if __name__ == "__main__":
    print("Parsing files...")
    all_data = parse_files()
    
    if not all_data:
        print("No data found. Ensure files named results_k_i.txt exist.")
    else:
        print("Generating Matching Size graphs...")
        plot_matching_size_vs_i(all_data)
        
        print("Generating Execution Time graphs...")
        plot_execution_time_vs_k(all_data)