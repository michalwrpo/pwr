import numpy as np
import networkx as nx
import random
import matplotlib.pyplot as plt

# --- Generowanie grafu ---
def generate_graph():
    G = nx.Graph()
    G.add_nodes_from(range(20))
    edges = [
        (0,1), (0,3), (1,4), (1,5), (2,3), (2,6),
        (3,7), (4,8), (5,9), (6,10), (7,11), (8,12),
        (9,13), (10,14), (11,15), (12,16), (13,17), (14,18),
        (15,19), (4,0), (6,1), (8,2), (10,5), (12,7), (14,9),
        (16,11), (17,18), (18,15), (19,16)
    ]
    G.add_edges_from(edges)
    return G

# --- Losowa macierz N ---
def generate_N(size, scale=1):
    N = np.random.randint(1, 50, size=(size, size)) * scale
    np.fill_diagonal(N, 0)
    return N

def scale_N(N, scale):
    for i in range(len(N)):
        for j in range(len(N[i])):
            N[i][j] *= scale
    return N

# --- Przydziel przepływy losowo ---
def assign_flows(G, N, scale=1):
    a = {e: 0 for e in G.edges()}

    for i in range(len(N)):
        for j in range(len(N[i])):
            path = nx.shortest_path(G, source=i, target=j)
            for k in range(len(path) - 1):
                try:
                    a[(path[k], path[k+1])] += int(N[i][j] * scale)
                except KeyError:
                    a[(path[k+1], path[k])] += int(N[i][j] * scale)
    return a

# --- Przypisanie przepustowości ---
def assign_capacities(m, a, scale=1.0):
    c = {e: 0 for e in G.edges()}
    for e in G.edges():
        c[e] = int(m * a[e] * (2 + random.random() / 2) * scale)
    return c

# --- Oblicz opóźnienie T ---
def compute_T(G, N, flows, capacities, m):
    total_packets = sum(sum(N))
    T = 0
    for e in G.edges():
        a, c = flows[e], capacities[e]
        if c > m * a:
            T += a / (c / m - a)
    return T / total_packets if total_packets else 0

# --- Symulacja niezawodności ---
def simulate_reliability(G, N, capacities, m, T_max, p, trials=500):
    success = 0
    for _ in range(trials):
        failed = False
        active_edges = [e for e in G.edges() if random.random() < p]
        subG = G.edge_subgraph(active_edges).copy()
        if nx.is_connected(subG) and subG.nodes == G.nodes:
            flows = assign_flows(subG, N)
            for e in subG.edges:
                if capacities[e] <= m * flows[e]:
                    failed = True
                    break
            if not failed:
                T = compute_T(subG, N, flows, capacities, m)
                if T < T_max:
                    success += 1
    return success / trials

def experiment_1(G, N):
    T_max = 0.05
    p = random.randint(960, 1000)/1000
    m = 1000
    scales = np.linspace(1.0, 4.0, 10)
    results = []
    base_flows = assign_flows(G, N)
    capacities = assign_capacities(m, base_flows)

    for _ in range(10):
        N = scale_N(N, 1.05)
        reliability = simulate_reliability(G, N, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(scales, results, marker='o')
    plt.xlabel("Współczynnik skali macierzy N")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Natężenie strumienia")
    plt.grid(True)
    plt.savefig("experiment1.png")
    plt.show()

def experiment_2(G, N):
    flows = assign_flows(G, N, scale=1.5)
    m = 1000
    T_max = 0.05
    p = random.randint(960, 1000)/1000
    scales = np.linspace(1.0, 4.0, 10)
    results = []

    for scale in scales:
        capacities = assign_capacities(m, flows, scale)
        reliability = simulate_reliability(G, N, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(scales, results, marker='s', color='green')
    plt.xlabel("Średnia przepustowość kanałów (bps)")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Przepustowość")
    plt.grid(True)
    plt.savefig("experiment2.png")
    plt.show()

def experiment_3(G, N):
    extra_edges = [(4,19), (6,11), (8,12), (10,15), (6,12), (14,19), (1,16), (3,17), (5,18), (6,19)]
    N = scale_N(N, 0.9)
    T_max = 0.05
    p = random.randint(960, 1000)/1000
    m = 1000
    scale = 1.3
    results = []
    flows = assign_flows(G, N, scale)
    capacities = assign_capacities(m, flows)
    mean_cap = int(np.mean(list(capacities.values())))

    for i in range(len(extra_edges) + 1):
        if i > 0:
            G.add_edge(extra_edges[i-1][0], extra_edges[i-1][1])

        N = generate_N(len(G.nodes()))
        capacities[extra_edges[i-1]] = mean_cap
        reliability = simulate_reliability(G, N, capacities, m, T_max, p)
        results.append(reliability)

    plt.figure()
    plt.plot(range(len(results)), results, color='orange')
    plt.xlabel("Liczba dodatkowych krawędzi")
    plt.ylabel("Pr[T < T_max]")
    plt.title("Niezawodność vs Rozbudowa topologii")
    plt.grid(True)
    plt.savefig("experiment3.png")
    plt.show()

if __name__ == "__main__":
    G = generate_graph()
    N = generate_N(len(G.nodes))

    experiment_1(G, N)
    experiment_2(G, N)
    experiment_3(G, N)
