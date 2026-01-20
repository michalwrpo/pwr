import matplotlib.pyplot as plt
import numpy as np
import os

def parse_results(path="output"):
    """
    Reads files results_1.txt to results_16.txt.
    Returns dictionaries mapping k to lists of values.
    """
    k_values = []
    
    # Data containers: key = k, value = list of 100 measurements
    data_flows = {}
    data_times = {}
    data_paths = {}

    for k in range(1, 17):
        filename = f"{path}/results_{k}.txt"
        
        if not os.path.exists(filename):
            continue
            
        k_values.append(k)
        data_flows[k] = []
        data_times[k] = []
        data_paths[k] = []

        try:
            with open(filename, 'r') as f:
                lines = f.readlines()
                
                # Iterate through lines in pairs
                i = 0
                while i < len(lines) - 1:
                    line1 = lines[i].strip()
                    line2 = lines[i+1].strip()
                    
                    if not line1 or not line2:
                        i += 1
                        continue

                    if line1.startswith("Max Flow:"):
                        flow_str = line1.replace("Max Flow:", "").replace(".", "").strip()
                        data_flows[k].append(int(flow_str))
                    
                    parts = line2.split()
                    if len(parts) >= 2:
                        data_times[k].append(float(parts[0]))
                        data_paths[k].append(int(parts[1]))
                        
                    # Move to next pair
                    i += 2
        except Exception as e:
            print(f"Error reading {filename}: {e}")

    return sorted(k_values), data_flows, data_times, data_paths

def plot_metric(k_values, data_dict, data_dict2, metric_name, y_label, use_log_scale=False, fname='Average'):
    """
    Generates a plot for a specific metric showing mean and min-max range.
    """
    means = []
    mins = []
    maxs = []
    valid_ks = []

    means2 = []
    mins2 = []
    maxs2 = []
    valid_ks2 = []

    for k in k_values:
        if not data_dict[k]: # Skip if no data for this k
            continue
        
        valid_ks.append(k)
        values = np.array(data_dict[k])
        
        means.append(np.mean(values))
        mins.append(np.min(values))
        maxs.append(np.max(values))

        if not data_dict2[k]: # Skip if no data for this k
            continue

        valid_ks2.append(k)
        values2 = np.array(data_dict2[k])

        means2.append(np.mean(values2))
        mins2.append(np.min(values2))
        maxs2.append(np.max(values2))

    means = np.array(means)
    mins = np.array(mins)
    maxs = np.array(maxs)

    means2 = np.array(means2)
    mins2 = np.array(mins2)
    maxs2 = np.array(maxs2)

    plt.figure(figsize=(10, 6))    
    plt.plot(valid_ks, means, label="Dinic", color='blue', marker='o')
    plt.plot(valid_ks2, means2, label="Edmonds-Karp", color='orange', marker='o')
    plt.fill_between(valid_ks, mins, maxs, color='blue', alpha=0.2, label='Min-Max Range')
    plt.fill_between(valid_ks2, mins2, maxs2, color='orange', alpha=0.2, label='Min-Max Range EK')
    
    plt.title(f'{metric_name} vs Input Size (k)')
    plt.xlabel('k (Graph Size $2^k$)')
    plt.ylabel(y_label)
    plt.xticks(valid_ks)
    plt.grid(True, which="both", ls="-", alpha=0.4)
    
    if use_log_scale:
        plt.yscale('log')
        plt.ylabel(f'{y_label} (Log Scale)')

    plt.legend()
    plt.tight_layout()
    
    filename = f"plots/ex4_{metric_name.lower().replace(' ', '_')}.png"
    plt.savefig(filename)
    print(f"Generated plot: {filename}")

def main():
    k_values, flows, times, paths = parse_results()
    _, flows_ek, times_ek, paths_ek = parse_results(path="../ex1/output")

    if not k_values:
        print("No results files found (results_k.txt).")
        return

    plot_metric(k_values, flows, flows_ek, "Max Flow", "Flow Value", use_log_scale=True)
    # plot_metric(k_values, {k: [i/(k*2**k) for i in flows[k]] for k in flows}, "Max Flow Comparison", "Normalized flow", use_log_scale=False, fname="$flow / k \\cdot 2^k$")
    
    plot_metric(k_values, times, times_ek, "Execution Time", "Time (seconds)", use_log_scale=True)
    # plot_metric(k_values, {k: [10**9*i/(k * 2**(2*k)) for i in times[k]] for k in times}, "Execution Time Comparison", "Normalized time", use_log_scale=True, fname="$10^9 \\cdot time / (k \\cdot 2^{2k})$")

    plot_metric(k_values, paths, paths_ek, "Augmenting Paths", "Count", use_log_scale=True)
    # plot_metric(k_values, {k: [i/(k**(1.5)*2**(1/2*k)) for i in paths[k]] for k in paths}, "Augmenting Paths Comparison", "Normalized Count", use_log_scale=False, fname="$paths / (k^{1.5} \\cdot 2^{k/2})$")

if __name__ == "__main__":
    main()