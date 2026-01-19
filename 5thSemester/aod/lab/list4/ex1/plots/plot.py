import matplotlib.pyplot as plt
import numpy as np
import os

def parse_results():
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
        filename = f"output/results_{k}.txt"
        
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

def plot_metric(k_values, data_dict, metric_name, y_label, use_log_scale=False):
    """
    Generates a plot for a specific metric showing mean and min-max range.
    """
    means = []
    mins = []
    maxs = []
    valid_ks = []

    for k in k_values:
        if not data_dict[k]: # Skip if no data for this k
            continue
        
        valid_ks.append(k)
        values = np.array(data_dict[k])
        
        means.append(np.mean(values))
        mins.append(np.min(values))
        maxs.append(np.max(values))

    means = np.array(means)
    mins = np.array(mins)
    maxs = np.array(maxs)

    plt.figure(figsize=(10, 6))    
    plt.plot(valid_ks, means, label='Average', color='blue', marker='o')
    plt.fill_between(valid_ks, mins, maxs, color='blue', alpha=0.2, label='Min-Max Range')
    
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
    
    filename = f"plots/plot_{metric_name.lower().replace(' ', '_')}.png"
    plt.savefig(filename)
    print(f"Generated plot: {filename}")

def main():
    k_values, flows, times, paths = parse_results()

    if not k_values:
        print("No results files found (results_k.txt).")
        return

    plot_metric(k_values, flows, "Max Flow", "Flow Value", use_log_scale=True)
    plot_metric(k_values, times, "Execution Time", "Time (seconds)", use_log_scale=True)
    plot_metric(k_values, paths, "Augmenting Paths", "Count", use_log_scale=True)

if __name__ == "__main__":
    main()